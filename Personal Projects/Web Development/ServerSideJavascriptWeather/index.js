//import express library
const express = require( 'express' );

//import NEDB database
const Datastore = require( 'nedb' );

//Require file delete libraries
const fs = require('fs');

//Create path to delete 
const path = './public/uploads/upload.php'

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

	///response.json({test:123});
});

//Send data to the database
app.post( '/api', ( request, response ) =>
	{
		const data = request.body;
		const timestamp = Date.now();
		data.timestamp = timestamp;

		console.log( request.body );

		database.insert( data );

		//Clean the upload file
		cleanUploadFile();

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

//Create function to upload files
function cleanUploadFile() 
{
	try {
		fs.unlinkSync(path)
	} catch(err) {
		console.error(err)
	}
}

//Convert image data in base 64
function convertImgto64()
{

}