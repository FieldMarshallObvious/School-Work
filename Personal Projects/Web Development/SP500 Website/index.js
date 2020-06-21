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

//Set CORS origin
const corsOptions = {
	origin: 'http://localhost:3000/'
}

//Update the database
updateDataInDatabase();

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

//Returns hex code color of guage based on posistion
app.get( '/guage_color/:minmaxmiddle', async(request, response) =>
{
	//Variable delcarations
	const minmaxmiddle = request.params.minmaxmiddle.split(',');

	const min = minmaxmiddle[0];

	const max = minmaxmiddle[1];

	const middle = minmaxmiddle[2];

	let color = colorModule.determineGuageColor(min, max, middle);

	response.json(color);
});


//Callback function for database search
function readDatabase(err)
{
	console.log(err);
}

//Finds the index of desired information based on ID's
//Then returns the information in that index
function findInfo( database, indexInput )
{
	var output;
	database.find({}, (err, data) => {
		if (err)
		{
			response.end();
			return;
		}

		for( var i = 0; i < data.length; i++ )
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

//Function clears database
function clearDB()
{
	//Clear database
	db.remove({}, { multi: true }, function (err, numRemoved) {});
}

//Updates the data inside the database
async function updateDataInDatabase()
{
	//Get current date
	var date = new Date,
		year = date.getFullYear(),
		month = (date.getMonth() + 1),
		day = date.getDate();

	var curdate = [year, month, day].join('-');

	var newest_available_date;

	var radialGaugePosistion;

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