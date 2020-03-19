//import express library
const express = require( 'express' );
const app = express( );

//Tell the web application to listen for request at port 3000
app.listen( 3000, ( ) => console.log( 'listening at 3000' ) );

//Use express to serve static items
app.use( express.static( 'public' ) );


app.post( '/api', ( request, response ) =>
	{
		console.log( reuqest );
	} );