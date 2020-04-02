//Create map
const DBMap = L.map( 'DBMap' ).setView( [0, 0], 1 );

//Set market to invisble on first go
const marker = L.marker( [0,0] ).addTo( DBMap );
marker.setOpacity(0);

const attribution = '&copy; <a href="https://www.openstreetmap.org/copyright"OpenStreetMap</a> contributors';
const tileUrl = 'https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png';
const tiles = L.tileLayer( tileUrl, {attribution} );

let firstTime = true; 


//Add tiles to map
tiles.addTo( DBMap );

getData();


async function getData()
{
	//Get data from API
	const response = await fetch('/api');
	const data = await response.json();

	console.log(data);
	
	for( item of data )
	{	
		//Add a marker for each location in the database
		const marker = L.marker( [item.lat, item.long] ).addTo(DBMap);

		const input_lat = item.lat.toFixed(2);
		const input_long = item.long.toFixed(2);

		//Comprise all data in the array into a text 
		let txt = `The weather here at ${input_lat}°, ${input_long}°\nThe weather here is: ${item.weather.summary}\nWith a temperature of: ${item.weather.temperature}°C\n`;
		
		if( item.air_quality.reading == 'N/A' )
		{
			txt += 'no air quality reading.';
		}
		else
		{
			txt += `The concentration of particulate matter: ${item.air_quality.parameter}\nThe air quality is: ${item.air_quality.value} ${item.air_quality.unit}\nThe air quality data was last recorded: ${item.air_quality.lastUpdated}`;
		}

		marker.bindPopup(txt);
	}
}