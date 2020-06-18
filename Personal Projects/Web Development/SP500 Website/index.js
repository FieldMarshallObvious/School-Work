//import express library
const express = require ( 'express' );

//Import dotenv into app
require('dotenv').config();

//Import NEDB database
const Datastore = require( `nedb` );


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

//Update the database
updateDataInDatabase();

//Resolve CORS issues
app.use((req, res, next) => {
  	res.setHeader("Access-Control-Allow-Origin", "*");
  	res.setHeader(
    	"Access-Control-Allow-Methods",
    	"OPTIONS, GET, POST, PUT, PATCH, DELETE" // what matters here is that OPTIONS is present
  	);
  	res.setHeader("Access-Control-Allow-Headers", "Content-Type, Authorization");
  	next();
});

//Returns API data from database
app.get( '/index_key_ratios/:equity', aync(request, response) => 
{
	const index = request.params.index;
	findInfo(database, index).then((results) => 
	{
		console.log(index, ": ", results.shiller_pe);
		response.json([results.pe], [results.shiller_pe], [results.dividend_yield]);
	});
});
//Callback function for database search
function readDatabase(err)
{
	console.log(err);
}

//Finds the index of desired information based on ID's
//Then returns the information in that index
function findInfo( database, indexInput)
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

	//Clear data from last update
	database.remove({}, { multi: true }, function (err, numRemoved){});


	//Get SP500 data
	output = await API_interface.returnSP500( curdate, quandlApiKey, serverfetch );

	//Send all acquired data to the database
	database.insert( output );
}