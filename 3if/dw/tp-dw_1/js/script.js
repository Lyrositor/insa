var language;

/**
 * set the answer for a question
 * @param int           id      question number
 * @param string/{}/[]  answer  answer to write, if answer='-'
 *                              write nothing
 */
function setAnswer(id, answer) {
  var ans = document.getElementById('answer'+id);
  if (!answer){
    // doesn’t write
  }
  else if ( typeof answer === "string" ){
    ans.innerHTML = answer;
  }
  else if ( Array.isArray(answer) ){
    for ( var i = 0 ; i < answer.length ; i++ ){
      ans.appendChild(answer[i]);
    }
  }
  else if (typeof answer === "object"){
    ans.appendChild(answer);
  }
  else {
    console.log('unusable type for answer');
  }
  ans.parentNode.classList.remove('hidden');
}

/**
 * set buttons, answers and background to initial state
 */
function setButton() {
  for (var i = 1; i < 8 ; i++) {
    var ans = document.getElementById('answer'+i);
    if ( ! (ans.parentNode.classList.contains('hidden')) ){
      ans.parentNode.classList.add('hidden');
    }
  }
  if (document.body.style.backgroundColor != null){
    setBgColor(null);
    setTextColor('button1','#000000');
    document.getElementById('button1').style.backgroundColor = '#FFFFFF';
  }
}

/**
 * Set the background color to blue, button1 text to white and button1
 * background to black.
 */
function setButton1() {
    setButton();
    setBgColor('rgb(66, 139, 202)');
    setTextColor('button1','#FFFFFF');
    document.getElementById('button1').style.backgroundColor = "#000000";
    setAnswer(1, 'Faite.');
}

/**
 * get informations from calendar-short.xml
 */
function setButton2() {
  setButton();
  // show button3
  document.getElementById('button3').classList.remove('hidden');

  // look if the answer has already been given
  if ( document.getElementById('answer2').hasChildNodes() )
  {
    setAnswer(2);
    return;
  }

  // ---------------------------------- Get informations via xsl stylesheet
  var xmlDocument = getHttpXML('fichiersPourAjax/calendar-short.xml');
  var xslDocument = getHttpXML('stylesheets/calendar-eventlist-workaholics.xsl');

  var xsltProcessor = new XSLTProcessor();


  // Importation du .xsl
  xsltProcessor.importStylesheet(xslDocument);

  // Cr�ation du document XML transform� par le XSL
  var newXmlDocument = xsltProcessor.transformToDocument(xmlDocument);
  // Premier �l�ment "elementName" du nouveau document (par exemple, "ul", "table"...)
  var answer = newXmlDocument.getElementsByTagName('li')[0];

  // ------------------------------------------------ Add bootstrap classes
  answer.className = "media-list";
  answer.getElementsByTagName('h4')[0].className = "media-heading title";

  // ------------------------------------------- Append child to the answer
  setAnswer(2,answer);
}

/**
 * add informations from OMDb to answer2
 */
function setButton3() {
  setButton();

  // look if the answer has already been given
  if ( document.getElementById('answer3').hasChildNodes() )
  {
    setAnswer(3);
    return;
  }

  var answer = document.getElementById('answer2').firstChild;

  addInfos(answer);

  setAnswer(3,answer);
}

/**
 * get informations from calendar-full.xml
 */
function setButton4() {
  setButton();
  // show button5
  document.getElementById('button5').classList.remove('hidden');

  // look if the answer has already been given
  if ( document.getElementById('answer4').hasChildNodes() )
  {
    setAnswer(4);
    return;
  }

  // ---------------------------------- Get informations via xsl stylesheet

  var xmlDocument = getHttpXML('fichiersPourAjax/calendar-full.xml');
  var xslDocument = getHttpXML('stylesheets/calendar-eventlist.xsl');

  var xsltProcessor = new XSLTProcessor();


  // Importation du .xsl
  xsltProcessor.importStylesheet(xslDocument);

  // Cr�ation du document XML transform� par le XSL
  var newXmlDocument = xsltProcessor.transformToDocument(xmlDocument);
  // Get content of the answer and convert it into array
  var temp = newXmlDocument.getElementsByTagName('li');
  var panelContent = [];
  for (var i = 0; i < temp.length; i++) {
    panelContent[i] = temp[i];
  }

  // ---------------------------- generate panels and add bootstrap classes
  var answer = [];
  var panel = {};
  for ( var i = 0 ; i < panelContent.length ; i++ ){
    panelContent[i].className = "media-list panel-content ";
    panelContent[i].getElementsByTagName('h4')[0].className = "media-heading title";
    panel = document.createElement('div');
    panel.setAttribute("class","panel panel-default rollover panel-size");
    panel.appendChild(panelContent[i]);
    answer.push(panel);
  }

  // ------------------------------------------- Append child to the answer
  setAnswer(4,answer);
}

/**
 * add informations from OMDb to answer5
 */
function setButton5() {
  setButton();

  // look if the answer has already been given
  if ( document.getElementById('answer5').hasChildNodes() )
  {
    setAnswer(5);
    return;
  }

  // retrieve data from answer4 and convert it into an array
  var temp = document.getElementById('answer4').cloneNode(true).children;
  var answer = [];
  for (var i = 0; i < temp.length; i++) {
    answer[i] = temp[i];
  }

  // add informations missing on each node
  for (var i = 0; i < answer.length; i++) {
    addInfos(answer[i].firstChild);
  }

  // submit answer
  setAnswer(5,answer);
}

function setButton6() {

  // clear node
  var node = document.getElementById('answer6');
  while (node.lastChild) {
    node.removeChild(node.lastChild);
  }

  document.getElementById('search').value='';

  setButton();

  // enable search
  setAnswer(6);
}

function setButton7(language) {
  setButton();

  // Look if the answer has already been given
  if ( document.getElementById('answer7').hasChildNodes() )
  {
    if (window.language == language) {
      setAnswer(7);
      return;
    }
    else {
      var node =document.getElementById('answer7');
      while(node.lastChild) {
        node.removeChild(node.lastChild);
      }
      window.language = language;
    }
  }

  // ---------------------------------- Get informations via xsl stylesheet
  var xmlDocument = getHttpXML('petit_prince_3IF.xml');
  var xslDocument = getHttpXML('stylesheets/petit_prince_3IF.xsl');

  var xsltProcessor = new XSLTProcessor();

  // Import xsl stylesheet
  xsltProcessor.importStylesheet(xslDocument);

  // Set parameters for xsl stylesheet
  xsltProcessor.setParameter(null,'language',language);

  // Cr�ation du document XML transform� par le XSL
  var newXmlDocument = xsltProcessor.transformToDocument(xmlDocument);
  // Premier �l�ment "elementName" du nouveau document (par exemple, "ul", "table"...)
  var answer = newXmlDocument.getElementsByTagName('div')[0];

  // ------------------------------------------------ Add bootstrap classes

  setAnswer(7,answer);
}

function search() {

  // ---------------------------------- Get informations via xsl stylesheet

  var xmlDocument = getHttpXML('fichiersPourAjax/calendar-full.xml');
  var xslDocument = getHttpXML('stylesheets/calendar-eventlist-param.xsl');

  var xsltProcessor = new XSLTProcessor();


  // Import xsl stylesheet
  xsltProcessor.importStylesheet(xslDocument);

  // Add parameters for search
  xsltProcessor.setParameter(null,'serie',document.getElementById('search').value);

  // Cr�ation du document XML transform� par le XSL
  var newXmlDocument = xsltProcessor.transformToDocument(xmlDocument);
  // Get content of the answer and convert it into array
  var temp = newXmlDocument.getElementsByTagName('li');
  var panelContent = [];
  for (var i = 0; i < temp.length; i++) {
    panelContent[i] = temp[i];
  }

  // ---------------------------- generate panels and add bootstrap classes
  var answer = [];
  var panel = {};
  for ( var i = 0 ; i < panelContent.length ; i++ ){
    panelContent[i].className = "media-list panel-content ";
    panelContent[i].getElementsByTagName('h4')[0].className = "media-heading title";
    panel = document.createElement('div');
    panel.setAttribute("class","panel panel-default rollover panel-size");
    panel.appendChild(panelContent[i]);
    answer.push(panel);
  }
  var node = document.getElementById('answer6');
  while (node.lastChild) {
    node.removeChild(node.lastChild);
  }
  setAnswer(6,answer);

}

/**
 * add informations to the current node (for questions 3 and 5)
 * @param object node current node
 */
function addInfos(node) {
  var title = node.getElementsByTagName('h4')[0].textContent;
  var json = getHttpJSON('http://www.omdbapi.com/?t='+title+'&y=&plot=short&r=json');

  // Getting <a> element from the node
  var itemImageLink = node.firstChild;
  itemImageLink.setAttribute("class", "pull-left thumbnail-size");

  // Adding the thumnail
  var itemImage = document.createElement("img");
  itemImage.setAttribute("class", "media-object img-thumbnail responsive");
  itemImage.setAttribute("src", json.Poster);
  itemImageLink.appendChild(itemImage);

  // Adding description if it is missing
  if (node.lastChild.lastChild.textContent == ''){
    node.lastChild.lastChild.textContent = json.Plot;
  }

  // Adding informations
  var moreInfos = document.createElement("div");
  node.lastChild.lastChild.appendChild(moreInfos);

  // Creating labels for informations
  var yearLabel = document.createElement("span");
  yearLabel.setAttribute("class", "label label-default");
  yearLabel.innerHTML = json.Year;
  var ratedLabel = document.createElement("span");
  ratedLabel.setAttribute("class", "label label-default");
  ratedLabel.innerHTML = json.Rated;
  var releasedLabel = document.createElement("span");
  releasedLabel.setAttribute("class", "label label-default");
  releasedLabel.innerHTML = json.Released;
  var runtimeLabel = document.createElement("span");
  runtimeLabel.setAttribute("class", "label label-default");
  runtimeLabel.innerHTML = json.Runtime;
  var genreLabel = document.createElement("span");
  genreLabel.setAttribute("class", "label label-default");
  genreLabel.innerHTML = json.Genre;
  var languageLabel = document.createElement("span");
  languageLabel.setAttribute("class", "label label-default");
  languageLabel.innerHTML = json.Language;
  var countryLabel = document.createElement("span");
  countryLabel.setAttribute("class", "label label-default");
  countryLabel.innerHTML = json.Country;
  var imdbRatingLabel = document.createElement("span");
  imdbRatingLabel.setAttribute("class", "label label-default");
  imdbRatingLabel.innerHTML = json.imdbRating;
  var imdbVotesLabel = document.createElement("span");
  imdbVotesLabel.setAttribute("class", "label label-default");
  imdbVotesLabel.innerHTML = json.imdbVotes;

  moreInfos.appendChild(yearLabel);
  moreInfos.appendChild(document.createTextNode (" "));
  moreInfos.appendChild(ratedLabel);
  moreInfos.appendChild(document.createTextNode (" "));
  moreInfos.appendChild(releasedLabel);
  moreInfos.appendChild(document.createTextNode (" "));
  moreInfos.appendChild(runtimeLabel);
  moreInfos.appendChild(document.createTextNode (" "));
  moreInfos.appendChild(genreLabel);
  moreInfos.appendChild(document.createTextNode (" "));
  moreInfos.appendChild(languageLabel);
  moreInfos.appendChild(document.createTextNode (" "));
  moreInfos.appendChild(countryLabel);
  moreInfos.appendChild(document.createTextNode (" "));
  moreInfos.appendChild(imdbRatingLabel);
  moreInfos.appendChild(document.createTextNode (" "));
  moreInfos.appendChild(imdbVotesLabel);
}

/**
 * Set the color of the background
 * @param string color color of the background
 */
function setBgColor(color){
    document.body.style.backgroundColor = color;
}

/**
 * Set the color of a text for an element.
 * @param string id    element id
 * @param string color color of the text
 */
function setTextColor(id, color){
    document.getElementById(id).style.color = color;
}

function getHttpXML(xmlDocumentUrl) {

  var httpAjax;

  httpAjax = window.XMLHttpRequest ?
    new XMLHttpRequest() :
    new ActiveXObject('Microsoft.XMLHTTP');

  if (httpAjax.overrideMimeType) {
    httpAjax.overrideMimeType('text/xml');
  }

  //chargement du fichier XML � l'aide de XMLHttpRequest synchrone (le 3� param�tre est d�fini � false)
  httpAjax.open('GET', xmlDocumentUrl, false);
  httpAjax.send();

  return httpAjax.responseXML;
}

function getHttpJSON(jsonDocumentUrl) {

  var httpAjax;

  httpAjax = window.XMLHttpRequest ?
                        new XMLHttpRequest() :
                        new ActiveXObject('Microsoft.XMLHTTP');

  if (httpAjax.overrideMimeType) {
    httpAjax.overrideMimeType('application/json');
  }

  // chargement du fichier JSON � l'aide de XMLHttpRequest synchrone (le 3� param�tre est d�fini � false)
  httpAjax.open('GET', jsonDocumentUrl, false);
  httpAjax.send();

  var responseData = eval("(" + httpAjax.responseText + ")");

  return responseData;
}
