const canvas = document.getElementById('canvas1');
const ctx = canvas.getContext('2d');

//Set canvas width to window width
canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

//Variable declarations
let particleArray = [];

//Handle mouse interactions
const mouse = {
	x: null,
	y: null,
	radius: 150
};

window.addEventListener('mousemove', function(event){
	mouse.x = event.x;
	mouse.y = event.y;
});

//Generate text on canvas
ctx.fillStyle = 'white';
ctx.font = '30px Verdana';
ctx.fillText('A', 0, 40);

//Get pixel data for the area within this square
const data = ctx.getImageData(0, 0, 100, 100);


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
		this.desnity = (Math.random() * 30) + 1;
	}

	//Draw the circular particle
	draw()
	{
		ctx.fillStyle = 'white';
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

		if( distance < 500 )
		{
			this.size = 50;
		}
		else
		{
			this.size = 3
		}

	}
}

//Initialize particle array
function init()
{
	//Create particle array
	particleArray = [];

	for( let i = 0; i < 500; i++)
	{
		let x = Math.random() * 500;
		let y = Math.random() * 500;
		particleArray.push(new Particle(x, y));
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
	requestAnimationFrame(animate);

	//implement recursion
	requestAnimationFrame(animate);
}

init();
animate();
