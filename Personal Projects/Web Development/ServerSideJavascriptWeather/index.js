//import express library
const express = require( 'express' );

//import NEDB database
const Datastore = require( 'nedb' );

//Pull node fetch function
const fetch = require( 'node-fetch' );

//Setup API key protection
require('dotenv').config();

console.log(process.env);

const app = express( );

//Tell the web application to listen for request at port 3000
app.listen( 3000, ( ) => console.log( 'listening at 3000' ) );

//Use express to serve static items
app.use( express.static( 'public' ) );

//Allow server to pasre incoming data as json
app.use( express.json( {limit: '1mb'} ) );


//Create new data base
const database = new Datastore('database.db');

//load old database
database.loadDatabase();

//send data to the client if requested
app.get( '/api', ( request, response ) => {
	database.find({}, (err, data) => {
		if (err)
		{
			response.end();
			return;
		}
		response.json( data );
	});

});

app.get( '/weather/:latlong', async ( request, response ) =>
{

	console.log(request.params);

	//Get data parameters from the client
	const latlong = request.params.latlong.split(',');

	const lat = latlong[0];

	const long = latlong[1];

	console.log(lat,long);

	//Get API Key
	const api_key =  process.env.API_KEY;


	//Get weather for current posistion using dark sky API
	const weahter_url = `https://api.darksky.net/forecast/${api_key}/${lat},${long}/?units=si`;
	const weather_response = await fetch(weahter_url);
	const weather_data = await weather_response.json();

	//Get air quality for current posistion using air quality API
	const aq_url = `https://api.openaq.org/v1/latest?coordinates=${lat},${long}`;
	const aq_response = await fetch(aq_url);
	const aq_data = await aq_response.json();

	const output = {
		weather: weather_data,
		air_quality: aq_data
	};

	//Send dark sky response
	response.json(output);
});

//Send data to the database
app.post( '/api', ( request, response ) =>
	{
		const data = request.body;
		const timestamp = Date.now();
		data.timestamp = timestamp;

		console.log( request.body );

		database.insert( data );

		//Sends data back to the client
		response.json({
			//Inform the client data was recieved
			status: 'success',

			//Send back data that was recieved
			latitude: request.body.lat,
			longitude: request.body.long,

			//Send back timestamp
			timestamp: timestamp
		});
	});