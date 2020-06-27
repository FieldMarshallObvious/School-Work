//import express library
const express = require ( 'express' );

//Import dotenv into app
require('dotenv').config();

//Import node fetch function
const serverfetch = require( 'node-fetch' );

//Import color module
const colorModule = require('./colorIterator');

//Import radial guage module
const radialGuage = require('./radialgaugelocation');

//Import NEDB database
const Datastore = require( `nedb` );

//Import CORS library
const cors = require('cors');

//Import unirest library
const unirest = require( 'unirest' );

//Import API_interface
const API_interface = require('./API_interface.js');

//Setup library to var app
const app = express( );

const port = process.env.PORT || 3000;

app.listen( port, ( ) => console.log( `listening at ${port}`) );


//Use express to server static
app.use( express.static( 'public' ) );

//if ctrl-c is called end the app
process.on('SIGINT', function() {
  	console.log( "\nGracefully shutting down from SIGINT (Ctrl-C)" );
  	
  	process.exit(1);
});

//Setup database
const database = new Datastore('database.db');

//Load old database
database.loadDatabase();

//Get quandlAPIkey from enviroment
const quandlApiKey = process.env.API_KEY_QUANDL;

//Get bloombergAPIkey from enviroment
const bloombergAPIkey = process.env.API_KEY_BLOOM;

//Set variable to keep track of last timestamp
var lastTimeStamp;
var lastPrice;

//Set timer variables
var thirtyminutes =  30 * 60000;
var oneday = 1440 * 60000;

//Set CORS origin
const corsOptions = {
	origin: 'http://localhost:3000/'
}

//Update the database
updateDataInDatabase();
updateEquityPrice();

//Update equity price every 30 minutes
setInterval(updateEquityPrice, thirtyminutes);

//Update Shiller Data every day
setInterval(updateDataInDatabase, oneday);


//Resolve CORS issues
app.use((req, res, next) => {
  	res.header("Access-Control-Origin", req.headers.origin);
  	res.header(
    	"Access-Control-Allow-Methods",
    	"OPTIONS, GET, POST, PUT, PATCH, DELETE" // what matters here is that OPTIONS is present
  	);
  	res.header("Access-Control-Allow-Headers", "Authorization, Cache-Control, Access-Control-Allow-Headers, Origin,Accept, X-Requested-With, Content-Type, Access-Control-Request-Method, Access-Control-Request-Headers");
  	next();
});

//Catch CORS errors
app.get('/without-cors', ( request, response, next ) => {
	response.json({ msg: 'A CORS issue has occured!' });
});

//Returns API data from database
app.get( '/index_key_ratios/:equity', async(request, response) => 
{
	const equity = request.params.equity;
	findInfo(database, equity).then((results) => 
	{
		response.json(results);
	});
});

//Returns current price of index
app.get( '/cur_index_price', async(request, response) =>
{
	findInfo(database, timestamp).then((results) => 
	{
		//Log the last price 
		lastPrice = results.price;
		response.json(results.price);
	});
});

app.get( '/last_index_price_comparisson/:curPrice', async(request,response) =>
{
	//Variable declarations
	var output; 

	const curPrice = request.params.curPrice;

	//Determine of the last price relative to the cur price
	if( curPrice > lastPrice )
		output = 1;
	else if( curPrice = lastPrice )
		output = 0;
	else
		output = -1;

	response.json(output);
});
//Returns hex code color of guage based on posistion
app.get( '/guage_color/:minmaxmiddle', async(request, response) =>
{
	//Variable declarations
	const minmaxmiddle = request.params.minmaxmiddle.split(',');

	const min = minmaxmiddle[0];

	const max = minmaxmiddle[1];

	const middle = minmaxmiddle[2];

	let color = colorModule.determineGuageColor(min, max, middle);

	response.json(color);
});

//Function clears database
function clearDB()
{
	//Clear database
	db.remove({}, { multi: true }, function (err, numRemoved) {});
}

//Finds the index of desired information based on ID's
//Then returns the information in that index
function findInfo( database, indexInput )
{
	var output,
		i;
	database.find({}, (err, data) => {
		if (err)
		{
			response.end();
			return;
		}

		for( i = 0; i <= data.length; i++ )
		{
			if(data[i].index == indexInput)
			{
				output = data[i];
				break;
			}
		}
		return output;
	});

	return new Promise( resolve => 
	{
		setTimeout(() => {
			if( output != undefined )
				resolve(output);
			else
				reject("Recovery failed");

		}, 2000, output);
	});
}

function getTimestamp()
{
	//Get current date to convert to 
	//Unix time
	var date = new Date,
		year = date.getFullYear(),
		month = (date.getMonth() + 1),
		day = date.getDate(),
		hour = date.getHours(),
		minute = date.getMinutes(),
		second = date.getSeconds();

	//Convert time to unix time and return after conversion
	var datum = new Date(Date.UTC(year,month-1,day,hour,minute,second));
 	return datum.getTime()/1000;

	}

//Callback function for database search
function readDatabase(err)
{
	console.log(err);
}

//Updates the data inside the database
async function updateDataInDatabase()
{
	//Variable declarations
	var radialGaugePosistion;

	//Get current date
	var date = new Date,
		year = date.getFullYear(),
		month = (date.getMonth() + 1),
		day = date.getDate();
	var curdate = [year, month, day].join('-');

	//Clear data from last update
	database.remove({}, { multi: true }, function (err, numRemoved){});

	//Get SP500 data
	output = await API_interface.returnSP500( curdate, quandlApiKey, serverfetch );

	radialGaugePosistion = radialGuage.determineGaugeLocation( output.index_pe, 15.76, output.shiller_pe, 16.71, output.dividend_yield, 4.32 );

	//add radial guage posistion to output object
	output.radial_pos = radialGaugePosistion;

	console.log( 'SP500: ', output );

	//Send all acquired data to the database
	database.insert( output );
}

//Updates the price of the equity
async function updateEquityPrice()
{
	//Variable declarations
	var output;

	//Get current hour
	var date = new Date,
		hour = date.getHours(),
		minute = date.getMinutes();

	if( !(hour >= 15 && minute >= 30) )
	{
		API_interface.returnPrice( bloombergAPIkey, serverfetch, unirest ).then((results) => 
		{
			console.log("Current Price of the index: ", results);
			
			//Get timestamp
			timestamp = getTimestamp();

			output = {
				price: results,
				index: timestamp
			};

			database.insert( output );
		});
	}
	else
	{
		console.log('Market is closed for the day');
		console.log('NOT CHECKING CURRENT PRICE');
	}
}