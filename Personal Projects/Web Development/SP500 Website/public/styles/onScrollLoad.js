//Variable declarations
var elements;
var windowHeight;

//This function initializes 
//vars
function init() {
  elements = document.querySelectorAll('.untouched');
  windowHeight = window.innerHeight;

  console.log(windowHeight);

  //If there are no untouched vars 
  //search for appearance
  if( elements.length == 0 )
  {
    elements = document.querySelectorAll('.appearance');
    windowHeight = window.innerHeight;
  }
}

//This functions checks if the DOM element
//is in view
function checkPosition() {
  //Check posistion for each element
  //foumd in query
  for (var i = 0; i < elements.length; i++) {
    var element = elements[i];

    //Get string for current element
    var elementClass = elements[i].className;
    var positionFromTop = elements[i].getBoundingClientRect().top;

    //Determine if the element needs to appear 
    //or disappear
    var appearTrue = positionFromTop - (windowHeight - windowHeight*0.16) <= 0;
    var disappearTrue = positionFromTop*0.2 + windowHeight >= windowHeight*0.11 + windowHeight;

    //If the element can appear, and 
    //cannot disappear, then make the element 
    //appear
    if ( appearTrue && !( disappearTrue ) ) {
      element.classList.add('appearance');
      element.classList.remove('untouched');
    }

    //If the element can disappear
    //and has the appearance class
    //then it make the element disappear
    if ( disappearTrue && elementClass.slice(elementClass.search('appearance'), elementClass.length) == 'appearance' )
    {
      element.classList.remove('appearance');
      element.classList.add('untouched');
    }
  }
}


//Run methods at least once
init();
checkPosition();

//Every time there is a scroll
//check if the DOM elements are in view
window.addEventListener('scroll', checkPosition);

//Every time there is a resize
//reintialize the vars
window.addEventListener('resize', init);
