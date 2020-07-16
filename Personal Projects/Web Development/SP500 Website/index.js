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
var price = [];

//Set timer variables
var thirtyminutes =  5 * 60000;
var oneday = 1440 * 60000;

//Set CORS origin
const corsOptions = {
	origin: 'http://localhost:3000/'
}

//Update the database
updateDataInDatabase();
updateEquityPrice();
updatePriceData();

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

		//If the price has not already been logged
		//push the cur price to the array
		if( results.price != price[price.length - 1] )
			price.push(results.price);


		response.json(results.price);
	});
});

app.get( '/last_index_price_comparisson/:curPrice', async(request,response) =>
{
	//Variable declarations
	var output,
		delta;

	const curPrice = request.params.curPrice;

	if( price.length > 1 )
		delta = 2;
	else
		delta = 1;

	console.log('The array is', price);
	console.log('CurPrice is: ', curPrice);
	console.log('Last Price is: ', price[ (price.length - delta) ]);

	//Determine of the last price relative to the cur price
	if( curPrice > price[ (price.length - delta) ] )
		output = 1;
	else if( curPrice == price[ (price.length - delta) ] )
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

//Returns historical price for index
app.get( '/historicalData/:equity', async(request, response) =>
{
	const equity = request.params.equity;
	findInfo(database, equity).then((results) => 
	{
		response.json(results);
	});
});

//Convert UNIX timestamp to human date
function convertTime(UNIXTime)
{
	//Convert data passed to function
	var date = new Date( UNIXTime * 1000 );

	var year = date.getFullYear( ),
		month = ( date.getMonth( ) + 1 ),
		day = date.getDate( );


	return (year + "-" + month + "-" + day);
}

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

		for( i = 0; i < data.length; i++ )
		{
			if(data[i].index == indexInput)
			{
				output = data[i];
				break;
			}
		}
		return output;
	});

	return new Promise( (resolve, reject) => 
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
		day = date.getDay(),
		hour = date.getHours(),
		minute = date.getMinutes();

	//Get new data only if market is open or if timestamp 
	//is undefined
	if( (!(hour >= 15 && minute >= 30) && day != 0 && day != 6) || typeof timestamp == "undefined" )
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

//Updates the price chart of the equity
async function updatePriceData()
{
	//Variable declarations
	var output,
		data = [],
		curJSON;

	API_interface.returnHistorical( bloombergAPIkey, serverfetch, unirest, "y1" ).then((results) => 
	{
		results.forEach( element => {

			//Get date from current item
			var formattedTimeStamp = convertTime( element.time );

			curJSON = {
				x: formattedTimeStamp,
				close: element.close
			};

			data.push(curJSON);
		});

		output = {
			priceHistory: data,
			index: `SP500Historical`
		};

		database.insert(output);

		console.log("Pushed data");
	});
}

