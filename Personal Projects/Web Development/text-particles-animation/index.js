const canvas = document.getElementById('canvas1');
const ctx = canvas.getContext('2d');

//Set canvas width to window width
canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

//Variable declarations
let particleArray = [];
let adjustX = -5;
let adjustY = -12;


//Handle mouse interactions
const mouse = {
	x: null,
	y: null,
	radius: 150
};

//Generate text on canvas
ctx.fillStyle = 'white';
ctx.font = '30px Verdana';
ctx.fillText('COOL', 0, 40);

//Get pixel data for the area within this square
const textCoordinates = ctx.getImageData(0, 0, canvas.height, canvas.width);


//Create class for particles
class Particle 
{
	constructor(x, y)
	{	
		this.x = x + 100;
		this.y = y;
		this.size = 3;
		this.baseX = this.x;
		this.baseY = this.y;
		this.density = (Math.random() * 40) + 5;
		this.distance = mouse.radius;
		this.Red = 255;
		this.Green = 255;
		this.Blue = 255;
	}

	//Draw the circular particle
	draw()
	{
		ctx.fillStyle = 'rgba( ' + this.Red + ', ' + this.Green + ', ' + this.Blue + '1)';
		ctx.beginPath();
		ctx.arc( this.x, this.y, this.size, 0, Math.PI * 2 );
		ctx.closePath();
		ctx.fill();
	}

	//Check if the particle is close to the mouse
	update()
	{
		//Variable declarations
		let dx = mouse.x - this.x;
		let dy = mouse.y - this.y;
		let distance = Math.sqrt(dx * dx + dy * dy);
		
		let forceDirectionX = dx / distance;
		let forceDirectionY = dy / distance;
		let maxDistance = mouse.radius;
		let force = ( maxDistance - distance ) / maxDistance;
		let directionX = force * forceDirectionX * this.density;
		let directionY = force * forceDirectionY * this.density;

		//If the particle is within the mouse radius
		//move the particle
		if( distance < mouse.radius )
		{
			this.x -= directionX * 3;
			this.y -= directionY * 3;

			calcColor( this, -1, distance );
		}

		//if the particle is not within the radius
		//check if it is still in its original posistion
		else
		{
			if ( this.x != this.baseX )
			{
				let dx = this.x - this.baseX;
				this.x -= dx/10;
			}

			if( this.y != this.baseY )
			{
				let dy = this.y - this.baseY;
				this.y -= dy/10;
			}

			calcColor( this, 1, distance );
		}

		//Assign distance to mouse
		this.distance = distance;

	}

}

//Initialize particle array
function init()
{
	//Create particle array
	particleArray = [];

	//Place pixels on regions that pass an opacity
	//test of greater than 50%
	for ( let y = 0, y2 = textCoordinates.height; y < y2; y++ )
	{
		for(let x = 0, x2 = textCoordinates.width; x < x2; x++ )
		{
			if( textCoordinates.data[(y * 4 * textCoordinates.width) +  (x * 4) + 3 ] > 128 )
			{
				let positionX = x + adjustX;
				let positionY = y + adjustY;

				particleArray.push( new Particle(positionX * 20, positionY * 20 ) );
			}
		}
	}
}


//Create animation for handling
//particle movement
function animate()
{
	ctx.clearRect(0, 0, canvas.width, canvas.height);

	for(let i = 0; i < particleArray.length; i++)
	{
		particleArray[i].draw();
		particleArray[i].update();
	}

	connect();

	//implement recursion
	requestAnimationFrame(animate);
}

//This function will connect particles
//with lines if they are close enough
function connect()
{
	//Variable declarations
	let dx;
	let dy;
	let opacityValue = 1;
	let distanceVal = 50;

	//Compare all particles if they
	//to see if they are close enough 
	//to connect lines
	for( let a = 0; a < particleArray.length; a++ )
	{
		for( let b = a; b < particleArray.length; b++ )
		{
			//Caculate distance
			dx = particleArray[a].x - particleArray[b].x;
			dy = particleArray[a].y - particleArray[b].y;

			let distance = Math.sqrt(dx * dx + dy * dy);

			if( distance < distanceVal )
			{
				//Calculate opactiy
				opacityValue = 1 - ( distance / distanceVal );

				if( particleArray[a].distance < mouse.radius )
				{	
					if( particleArray[a].distance < particleArray[b].distance || particleArray[a].distance == particleArray[b].distance )
						ctx.strokeStyle = 'rgba('+particleArray[a].Red+',' + particleArray[a].Green+ ','+ particleArray[a].Blue +',' + opacityValue + ')';
					else if ( particleArray[a].distance < particleArray[b].distance )
						ctx.strokeStyle = 'rgba('+particleArray[b].Red+',' + particleArray[b].Green+ ','+ particleArray[b].Blue +',' + opacityValue + ')';
				}

				else
				{
					ctx.strokeStyle = 'rgba( 255, 255, 255'+ opacityValue + ')';

				}


				ctx.lineWidth = 2;
				ctx.beginPath();
				ctx.moveTo(particleArray[a].x, particleArray[a].y);
				ctx.lineTo(particleArray[b].x, particleArray[b].y);
				ctx.stroke();
			}
		}
	}
}

//Calculate the color of the particle 
//based on it's distance to the particle
function calcColor( particle, operation, mouseDistance )
{
	//Variable declarations
	let temp;
	let conversionRate = 100.22;

	//Change the color of the particle
	//based on it's distance from the mouse
	for( let y = 0; y < particle.distance; y++ )
	{
		temp = operation * ( conversionRate ) + particle.Blue;
	}
	if( temp >= 0 && temp <= 255)
	{
		particle.Blue = temp;
	}

}

init();
animate();

//Handle mouse events
window.addEventListener('mousemove', function(event){
	mouse.x = event.x;
	mouse.y = event.y;
});

window.addEventListener('mouseout', function()
{
	mouse.x = undefined;
	mouse.y = undefined;
});

//Handle window resize evernts
window.addEventListener('resize', function(event)
{
	//Reset all items depdent on width and height
	canvas.width =  window.innerWidth;
	canvas.height =  window.innerHeight;

	const textCoordinates = ctx.getImageData(0, 0, canvas.height, canvas.width);

	init();
	animate();
});
