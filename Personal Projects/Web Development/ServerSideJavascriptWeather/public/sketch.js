const button = document.getElementById('button');

const UserMap = L.map( 'UserMap' ).setView( [0, 0], 1 );

//Set market to invisble on first go
const marker = L.marker( [0,0] ).addTo(UserMap);
marker.setOpacity(0);

const attribution = '&copy; <a href="https://www.openstreetmap.org/copyright"OpenStreetMap</a> contributors';
const tileUrl = 'https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png';
const tiles = L.tileLayer( tileUrl, {attribution} );

let firstTime = true; 


//Add tiles to map
tiles.addTo( UserMap );


//Function graphs and sets all data onto the webpage
async function displayData(lat, long, json)
{
	const latitude = lat;
	const longitude = long;

	//Set latitude and longtitude of marker
	marker.setLatLng( [latitude, longitude] );

	//Change view of map to the user if it's the first time
	//Also make the marker visible
	if  ( firstTime )
	{
		firstTime = false;

		//Set market to visible
		marker.setOpacity(1);


		//Updating view
		UserMap.setView( [latitude, longitude], 20 );
	}

	//If it's not the first time, update view
	//and marker location
	else
	{
		//Update marker
		marker.setLatLng( [latitude, longitude] );

		//Updating view
		UserMap.setView( [latitude, longitude], 20 );
	}
	

	//Set lat long data to span elements in the page
	document.getElementById( 'latitude' ).textContent = lat.toFixed(2);
	document.getElementById( 'longitude' ).textContent = long.toFixed(2);

	//Set weather data to span elements in the page
	document.getElementById( 'summary' ).textContent = json.currently.summary;
	document.getElementById( 'temperature' ).textContent = json.currently.temperature;
}
	

//This function is called whenever the button is pressed.
//After the button is pressed it will update the geolocation
button.addEventListener('click', async event => 
{


	//Check if the current location is available
	if ( 'geolocation' in navigator )
	{
		console.log( 'geolocation available' );

		navigator.geolocation.getCurrentPosition( async position => 
		{
			//Set latitude and long to the new posistion
			const lat = await position.coords.latitude;
			const long = await position.coords.longitude;

			//Get weather data for lat and long
			const api_url = `weather/${lat}, ${long}`;
			const weather_response = await fetch(api_url);
			const json = await weather_response.json();

			console.log(json);

			//Call function to map user location onto map
			//As well as write weather information
			displayData(lat, long, json.weather );

			//Post data to the server
			const data = { lat, long };

			//Creates settings for how to post data to server
			const options = {
				method:  'POST',
				headers: {
  					'Content-Type': 'application/json'
					},
				body: JSON.stringify(data)
			};

			//Post the data to the server
			//Also recieve as data for incoming info from the server
			const response = await fetch( '/api', options );

			const json_data = await response.json();

			console.log(json_data);

		});
	}

	else
	{
		console.log( 'geolocation not unavailable' );
	}
});