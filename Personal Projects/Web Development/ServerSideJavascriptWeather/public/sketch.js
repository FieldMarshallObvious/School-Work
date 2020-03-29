const button = document.getElementById('button');
const DOMIDs = ['latitude_info', 'longitude_info', 'weather_info'];



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

//Set all DOM elements to invisible until information has been entered
setAllDomOpacity( 0 );

//Remove all DOM margins
setAllMargin( 'none' );


//Function graphs and sets all data onto the webpage
async function displayData(lat, long, weather, aq)
{
	const latitude = lat;
	const longitude = long;

	const not_def = 'No data available';

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
	document.getElementById( 'summary' ).textContent = weather.currently.summary;
	document.getElementById( 'temperature' ).textContent = weather.currently.temperature;

	//Set air quality to span elements in the page
	try{
		document.getElementById( 'aq_particulate_matter' ).textContent = aq.parameter;
		document.getElementById( 'aq_value' ).textContent = aq.value;
		document.getElementById( 'aq_units' ).textContent = aq.unit;
		document.getElementById( 'aq_date' ).textContent = Date( aq.lastUpdated ).toLocaleString();
	} catch(error) {
		document.getElementById( 'aq_particulate_matter' ).textContent = not_def;
		document.getElementById( 'aq_value' ).textContent = ot_def;
		document.getElementById( 'aq_units' ).textContent = not_def;
		document.getElementById( 'aq_date' ).textContent = not_def;
	}
}

//This function sets all the DOM elements to a 
//passed opacity
function setAllDomOpacity(opacity)
{

	//For each dom element in the array set it to visible
	if( opacity == 1  )
	{
		DOMIDs.forEach( dom => setDomVisible(dom));
	}

	//For each dom element in the array set it to invisible
	else
	{
		DOMIDs.forEach( dom => setDomInvisible(dom));
	}
}

//This function sets a particular dom element to an 
//opacity of zero
function setDomInvisible(dom)
{
	document.getElementById( dom ).className = "invisble";
}

//This function sets a particular dom element to  an
//opacity of one
function setDomVisible(dom)
{
	document.getElementById( dom ).className = "visible";
}

//Set all the DOM margins based on user's choice
function setAllMargin(choice)
{
	//If the function calls none,
	//remove all margins and set last margin to negative
	if( choice == 'none'  )
	{
		DOMIDs.forEach( dom => setDomMarginZero(dom));

		//set the last DOM element to negative
		setDomMarginNegative( DOMIDs[DOMIDs.length - 1] );
	}

	//Else set all margins to default
	else
	{
		DOMIDs.forEach( dom => setDomMarginNormal(dom));
	}
}

//This function sets a particular DOM element to
//a margin of zero
function setDomMarginZero(dom)
{
	document.getElementById( dom ).style.margin = "0";
}

//This function sets a particular dom element to
//to a margin of -4em
function setDomMarginNegative(dom)
{
	document.getElementById( dom ).style.marginBottom = "-7em";
}

//This function sets a particular dom element to
//to a margin 1em
function setDomMarginNormal(dom)
{
	document.getElementById( dom ).style.marginBottom = "1em";
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
			displayData(lat, long, json.weather, json.air_quality.results[0].measurements[0] );

			//After text content of the DOM elements is set
			//give them opacity
			setAllDomOpacity( 1 );

			//After text content of the DOM elements is set
			//set their margins to normal
			setAllMargin( 'normal' );

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