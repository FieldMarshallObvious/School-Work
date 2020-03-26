//import express library
const express = require( 'express' );

//import NEDB database
const Datastore = require( 'nedb' );

//Pull node fetch function
const fetch = require( 'node-fetch' );

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

	//Get api for weather current posistion
	const api_url = "https://api.darksky.net/forecast/8f3f1bd51c4adb287b601101338e044f/${lat},${long}";

	const weather_response = await fetch(api_url);

	const json = await weather_response.json();

	//Send dark sky response
	response.json(json);
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