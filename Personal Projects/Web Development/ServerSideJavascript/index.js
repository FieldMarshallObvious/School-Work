//import express library
const express = require( 'express' );
const app = express( );

//Tell the web application to listen for request at port 3000
app.listen( 3000, ( ) => console.log( 'listening at 3000' ) );

//Use express to serve static items
app.use( express.static( 'public' ) );

//Allow server to pasre incoming data as json
app.use( express.json( {limit: '1mb'} ) );

app.post( '/api', ( request, response ) =>
	{
		console.log( request.body );

		//Sends data back to the client
		response.json({
			//Inform the client data was recieved
			status: 'success',

			//Send back data that was recieved
			latitude: request.body.lat,
			longitude: request.body.long
		});
	} );