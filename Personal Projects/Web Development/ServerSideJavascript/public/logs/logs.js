displayData();

async function displayData()
{
	console.log('In function');
	const response = await fetch('/api');

	console.log('In function');

	const data = await response.json();

	console.log(data);
	
	console.log('In function');
	for( item of data )
	{	
		console.log(item);
		//Create location to store data
		const root = document.createElement('div');
		const geo = document.createElement('div');
		const date = document.createElement('div');
		const image = document.createElement('img');

		//Add data to elements on page
		geo.textContent = `${item.lat}°, ${item.long}°`;

		//Convert date information into a proper date
		const dateString = new Date(item.timestamp).toLocaleString();
		date.textContent = dateString;

		//Convert image from base 64 to actual image
		image.src = item.image64;


		root.append(geo, date, image);
		document.body.append(root);

	}
	console.log(data);
}