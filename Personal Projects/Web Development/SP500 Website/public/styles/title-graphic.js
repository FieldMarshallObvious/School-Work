//Get dimensions, and set dimensions for canvas
const canvas = document.getElementById("mainGraphic");
const ctx = canvas.getContext('2d');
canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

let particlesArray;

//Get mouse posisiton
let mouse = {
	x: null,
	y: null,
	radius: (canvas.height/80) * (canvas.width/80)
}

//Listen for mouse movements
window.addEventListener('mousemove', 
	function(event) {
		mouse.x = event.x;
		mouse.y = event.y;
	}
);

//Creates particle
class Particle 
{
	constructor(x, y, directionX, directionY, size, color )
	{
		this.x = x;
		this.y = y;
		this.directionX = directionX;
		this.directionY = directionY;
		this.size = size;
		this.color = color;
	}

	//Method draws individual particle
	draw() 
	{
		ctx.beginPath();
		ctx.arc(this.x, this.y, this.size, 0, Math.PI * 2, false);
		ctx.fillStyle = '#FFFFFF';
		ctx.fill();
	}

	//Check particle posistion, and mouse posistion
	//move the particle then draw the particle
	update() 
	{
		//Variable declarations
		let dx,
			dy,
			distance;
		//Check if particle is still within canvas
		//If the particle is not within the canvas
		//Move the particle
		if( this.x > canvas.width || this.x < 0 )
		{
			this.directionX = -this.directionX;
		}
		if( this.y > canvas.height || this.y < 0 )
		{
			this.directionY = -this.directionY;
		}

		//Check if the particle has collided
		//with the mouse
		dx = mouse.x - this.x;
		dy = mouse.y - this.y;
		distance = Math.sqrt( dx*dx + dy*dy );


		if( distance == mouse.radius + this.size + 20 )
		{
			if( mouse.x < this.x && this.x < canvas.width - this.size * 10 )
			{
				this.x+=10;
			}

			if( mouse.x > this.y && this.x >this.size * 10 )
			{
				this.x-=10;
			}
			if( mouse.y < this.y && this.y < canvas.height - this.size * 10 )
			{
				this.y+=10;
			}

			if( mouse.y > this.y && this.y >this.size * 10 )
			{
				this.y-=10;
			}

		}

		if( distance < mouse.radius + this.size )
		{
			if( mouse.x < this.x && this.x < canvas.width - this.size * 10 )
			{
				this.x +=10;
			}

			if ( mouse.x > this.x && this.x > this.size * 10)
			{
				this.x -=10;
			}

			if( mouse.y < this.y && this.y < canvas.height - this.size * 10 )
			{
				this.y +=10;
			}

			if ( mouse.y > this.y && this.y > this.size * 10)
			{
				this.y -=10;
			}
		}

		//move particle
		this.x += this.directionX;
		this.y += this.directionY;

		//draw particle
		this.draw( );

	}
}

// Creates array of particles
function init() 
{
	//Variable declarations
	particlesArray = [];
	let numberOfParticles  = ( canvas.height * canvas.width ) / 10000;
	let size, x, y, directionX, directionY, color;

	//Create particles for each item in the array
	for( let i = 0; i < numberOfParticles; i ++ )
	{
		size = ( Math.random( ) * 5 ) + 1;
		x = ( Math.random( ) * ( ( innerWidth - size * 2 ) - ( size * 2 ) ) + size * 2 );
		y = ( Math.random( ) * ( ( innerHeight - size * 2 ) - ( size * 2 ) ) + size * 2 );

		directionX = (Math.random() * 5) - 2.5;
		directionY = (Math.random() * 5) - 2.5;

		color = '#FFFFFF';

		particlesArray.push( new Particle(x, y, directionX, directionY, size, color ) );
	}
}

// Creates animation for particles
function animate() 
{
	requestAnimationFrame(animate);
	ctx.clearRect( 0, 0, innerWidth, innerHeight );

	//Update each particle in the array
	for( let i = 0; i < particlesArray.length; i++ )
	{
		particlesArray[i].update();
	}
	 connect();

}

// Connect particle together if the distance
// is close enough
function connect()
{
	//Variable declarations
	let opacityValue = 1;
	for ( let a = 0; a < particlesArray.length; a++ )
	{
		for( let b = a; b < particlesArray.length; b++ )
		{
			let distance = ( ( particlesArray[a].x - particlesArray[b].x ) * ( particlesArray[a].x - particlesArray[b].x ) ) 
						   + ( ( particlesArray[a].y - particlesArray[b].y ) * ( particlesArray[a].y - particlesArray[b].y ) );

			//If the distance is close enough, connect
			//the particles
			if( distance < (canvas.width/7) * (canvas.height/7))
			{	
				opacityValue = 1 - (distance/20000);
				//Set stroke style of lines
				ctx.strokeStyle= `rgba(255,255,255,${opacityValue})`;
				ctx.lineWidth = 1;

				//begin path
				ctx.beginPath();

				//Create the line
				ctx.moveTo( particlesArray[a].x, particlesArray[a].y );
				ctx.lineTo( particlesArray[b].x, particlesArray[b].y );
				ctx.stroke();

			}
		}
	}
}

//resive event listener
window.addEventListener('resize',
	function() {
		//Resize canvas for new dimensions
		//Also modify mouse radius to match new window size
		canvas.width = innerWidth;
		canvas.height = innerHeight;
		mouse.radius = ((canvas.height/80) * (canvas.height/80));
		init();
	});

//If the mouse leaves the window
//prevent nodes from interacting with where
//the mouse last was
window.addEventListener('mouseout',
	function() 
	{
		mouse.x = undefined;
		mouse.y = undefined;
	});

init();
animate();
