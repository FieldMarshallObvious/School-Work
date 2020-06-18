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
	
});

//Callback function for database search
function readDatabase(err)
{
	console.log(err);
}

//Updates the data inside the database
async function updateDataInDatabase()
{

}