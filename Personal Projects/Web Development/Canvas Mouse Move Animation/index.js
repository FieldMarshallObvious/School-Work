//Get canvas and drawin tools
const canvas = document.getElementById('canvas1');
const ctx = canvas.getContext('2d');
canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

ctx.textBaseline = 'middle';

//Variable declarations
let lettersArray = ['C', 'O', 'O', 'L'];
let hue = 0;
let particles = [];
let numberofParticles = (canvas.width * canvas.height ) / 5000;

console.log("number of particles", numberofParticles);

const mouse = {
	x: 0,
	y: 0,
	radius: 20,
	autopilotAngle: 0,
}

//Every time the mouse moves
//grab the x and of the new 
//posistion
window.addEventListener('mousemove', function(e){
	mouse.x = event.x;
	mouse.y = event.y;
});

//This class creates the
//particle object
class Particle 
{
	constructor( x, y, radius )
	{
		this.x = x;
		this.y = y;
		this.radius = radius;
		this.color = 'hsl(' + hue + ', 100%, 50%)';
		this.text = lettersArray[Math.floor( Math.random( ) * lettersArray.length )];
	}

	//This method draws the 
	//object circle
	draw( )
	{
		//Create arc path
		ctx.beginPath( );
		ctx.arc( this.x, this.y, this.radius, 0, Math.PI * 2 );

		//Fill path with color
		ctx.fillStyle = this.color;

		//End path
		ctx.closePath( );
		ctx.fill( );

		//Draw reflection patch
		ctx.beginPath();
		ctx.arc(this.x, this.y, this.radius * 0.8, 0, Math.PI * 1.5, true);
		ctx.fillStyle = 'white';
		ctx.fill();

		//Drawing text
		ctx.font = this.radius + 'px Verdana';
		ctx.fillText(this.text, this.x - this.radius/2.7, this.y);
	}

	//This function moves moves the trail
	//if the mouse stops providing
	//input
	autoMove() 
	{
		if( mouse.x == undefined && mouse.y == undefined )
		{
			let newX = mouse.radius * canvas.width/50 * Math.cos(mouse.autopilotAngle * (Math.PI/180));

			let newY = mouse.radius * canvas.height/50 * Math.sin(mouse.autopilotAngle * (Math.PI/90));

			mouse.x = newX + canvas.width/2;
			mouse.y = newY + canvas.height/2;
		}
		mouse.autopilotAngle += 0.01;
	}
}

//This function 
//initializes all particles,
//determined by number of particles
//Also prevent particles from 
//overlapping
function handleOverlap()
{
	//Variable declarations
	let overlapping = false;
	let protection = 500;
	let counter = 0;

	//Create random posistion around mouse for particle
	while( particles.length < numberofParticles && counter < protection )
	{
		let randomAngle = Math.random() * 2 * Math.PI;

		let randomRadius = mouse.radius * Math.random();

		let particle = {
			x: mouse.x + randomRadius + Math.cos(randomAngle),
			y: mouse.y + randomRadius + Math.sin(randomAngle),
			radius: Math.floor(Math.random() * 30) + 10,
		};

		overlapping = false;

		//Check for particles that collide
		for( let i = 0; i < particles.length; i++ )
		{
			let previousParticle = particles[i];

			let dx = particle.x - previousParticle.x;
			let dy = particle.y - previousParticle.y;
			let distance = Math.sqrt( dx * dx + dy * dy);

			if( distance < (particle.radius + previousParticle.radius) )
			{
				overlapping = true;
				break;
			}

		}

		//If there is no overlap, add the paritcle
		//to the array
		if( !overlapping )
		{
			particles.unshift(new Particle(particle.x, particle.y, particle.radius));
		}

		counter++;
	}

}

//This function creates animation
//loop
function animate(  )
{
	ctx.clearRect( 0, 0, canvas.width, canvas.height );
	
	//For each particle in the array draw it	
	for( let i = 0; i < particles.length; i++ )
	{
		particles[i].draw();
		particles[i].autoMove();
	}

	handleOverlap();
	//Remove old particles
	if ( particles.length >= numberofParticles )
	{
		for( let i = 0; i < 3; i++ )
		{
			particles.pop();
		}
	}

	//Increment hue
	hue+=2;
 
	//Implement recursion
	requestAnimationFrame(animate);
}

animate();

window.addEventListener("resize", function(){
    particles = [];
    canvas.width = window.innerWidth;
    canvas.height = window.innerHeight;
    numberofParticles =  (canvas.width * canvas.height ) / 5000;
    ctx.textBaseline = "middle";
    radius = window.innerWidth/5;
    handleOverlap();
});

let autopilot = setInterval(function(){
        mouse.x = undefined;
        mouse.y = undefined;
}, 4);

canvas.addEventListener("mouseleave", function(){
    autopilot = setInterval(function(){
        mouse.x = undefined;
        mouse.y = undefined;
    }, 4);
});

canvas.addEventListener("mouseenter", function(){
    clearInterval(autopilot);
    autopilot = undefined;
});
