import logo from './logo.svg';
import './App.css';
import axios from 'axios';
import * as go from 'gojs';
import * as d3 from 'd3';
let loadOption = "gen";
let topFrom = "NULL";
let topTo = "NULL";
let topsNum = "NULL";

function App() {
  return (
    <div className='main'>
      <div className='side-bar'>
        <nav>
        <button className='side-bar-button'
          onClick={() => {
            const element= document.getElementById("popup");
            element.style.visibility = "visible";
            resetVars()
          }}>
            Завантажити дані</button>
        <button className='side-bar-button'
        onClick={(event) => processData(event)}>Запустити програму</button>
        <button className='side-bar-button'>Зберегти зображення</button>

        <marquee>Text</marquee>
        </nav>


      </div>
      <div id="myDiagramDiv">
        <svg width="960" height="600"></svg>
        </div>
      <div className='popup' id='popup'>
        <div className='popup__body'>
          <div className='popup__content'>
            <div className='radiobuttons'>
              <label htmlFor="loadRadioId" className="radio">
                <input type="radio" name="radioField" id="loadRadioId" className="radio__input" 
                onClick={() => {
                  loadOption="file";
                }}></input>
                <div className='radio__radio'></div>
                Завантажити з файлу
              </label>
              <label htmlFor="loadRadioId2" className="radio" >
                <input type="radio" name="radioField" id="loadRadioId2" className="radio__input" defaultChecked 
                onClick={() => {
                loadOption="gen";
              }}></input>
                <div className='radio__radio'></div>
                Згенерувати
              </label>
            </div>
            <div className='popup__text'>
              <label id='text__topsnum'>Кількість вершин</label>
              <input type='text' id='field__topsnum' className='no-focusborder' 
              onChange={(event) => isNumber(event)}></input>
            </div>
            <div className='popup__text'>
              <label id='text__topfrom'>Пошук з вершини</label>
              <input type='text' id='field__topfrom' className='no-focusborder'
              onChange={(event) => isNumber(event)}></input>
            </div>
            <div className='popup__text'>
              <label id='text__topto'>Пошук до вершини</label>
              <input type='text' id='field__topto' className='no-focusborder'
              onChange={(event) => isNumber(event)}></input>
            </div>
            <input id="file-input" type="file" name="file" onChange={(event) => uploadFile(event)} multiple></input>
            <button className='side-bar-button' id='run-button'
              onClick={(event) => uploadData(event)}
              >Завантажити</button>
            <button className='side-bar-button' 
              onClick={() => {
                const element= document.getElementById("popup");
                element.style.visibility = "hidden";
                clearVal()
              }}>Вийти</button>
          </div>
        </div>
      </div>

      
    </div>
  )

}

export default App;


function processData(event){
  //initilize svg or grab svg
  var svg = d3.select("svg");
  var width = svg.attr("width");
  var height = svg.attr("height");

  var graphData = {
    nodes: [{ name: "A" }, { name: "B" }, { name: "C" }, { name: "D" }],
    links: [
      { source: "A", target: "B" },
      { source: "B", target: "C" },
      { source: "D", target: "C" }
      
    ]
  };

  var simulation = d3
  .forceSimulation(graphData.nodes)
  .force("charge", d3.forceManyBody().strength(-30))
  .force("center", d3.forceCenter(width / 2, height / 2))
  .force("link", d3.forceLink(graphData.links).id(d => d.name))
  .force("link",d3.forceLink(graphData.links).distance(100))
  .on("tick", ticked);

  var links = svg
    .append("g")
    .selectAll("line")
    .data(graphData.links)
    .enter()
    .append("line")
    .attr("stroke-width", 3)
    .attr("height", 30)
    .style("stroke", "orange")
    .text("Hello world")
    .attr('marker-start', "url(#arrow)")
    ;

  var drag = d3
    .drag()
    .on("start", dragstarted)
    .on("drag", dragged)
    .on("end", dragended);

    svg.append("svg:defs").append("svg:marker")
    .attr("id", "arrow")
    .attr("viewBox", "0 -5 10 10")
    .attr('refX', -93) //so that it comes towards the center.
    .attr("markerWidth", 3)
    .attr("markerHeight", 3)
    .attr("orient", "auto")
    .append("svg:path")
    .attr("d", "M0,-5L10,0L0,5");

  var textsAndNodes = svg
    .append("g")
    .style("font", "10px times")
    .selectAll("g")
    .data(graphData.nodes)
    .enter()
    .append("g")
    .call(drag);


  var circles = textsAndNodes
    .append("circle")
    .attr("r", 10)
    .attr("fill", "red");

  var texts = textsAndNodes.append("text").text(function(d) {
    return d.name;
  });

  function ticked() {
    //translate(x, y)
    textsAndNodes.attr("transform", function(d) {
      return "translate(" + d.x + ", " + d.y + ")";
    });

    links
      .attr("x1", function(d) {
        return d.source.x;
      })
      .attr("y1", function(d) {
        return d.source.y;
      })
      .attr("x2", function(d) {
        return d.target.x;
      })
      .attr("y2", function(d) {
        return d.target.y;
      });
    console.log(simulation.alpha());
  }

  function dragstarted(d) {
    //your alpha hit 0 it stops! make it run again
    simulation.alphaTarget(0.3).restart();
    d.fx = event.x;
    d.fy = event.y;
  }
  function dragged(d) {
    d.fx = event.x;
    d.fy = event.y;
  }

  function dragended(d) {
    // alpha min is 0, head there
    simulation.alphaTarget(0);
    d.fx = null;
    d.fy = null;
  }
}

function isNumber(event)
{
  var clickedId = event.target.id;
  var inputedText= document.getElementById(clickedId).value;

  if(!validation.isNumber(inputedText)){
    document.getElementById(clickedId).style.borderColor = "red";
    setVal(clickedId,"NULL");
  }
  else if (validation.moreThan(inputedText)){
    document.getElementById(clickedId).style.borderColor = "red";
    setVal(clickedId,"NULL");
  }
  else {
    document.getElementById(clickedId).style.borderColor = "green";
    setVal(clickedId,inputedText);
  }
}

function setVal(clickedId, val){
  if(clickedId=="field__topsnum") {topsNum=val}
  else if (clickedId=="field__topfrom") {topFrom=val}
  else if (clickedId=="field__topto") {topTo=val}
}

function clearVal()
{
  document.getElementById("field__topsnum").value=""
  document.getElementById("field__topfrom").value=""
  document.getElementById("field__topto").value=""
}

var validation = {
  isNotEmpty:function (str) {
      var pattern =/\S+/;
      return pattern.test(str);  // returns a boolean
  },
  isNumber:function(str) {
      var pattern = /^\d+\.?\d*$/;
      return pattern.test(str);  // returns a boolean
  },
  moreThan:function(str) {
    if (Number(str)>1000) {return true}
    else return false;
  }
}; 

function checkAllComponents() {
  if(topsNum!="NULL"&&topFrom!="NULL"&&topTo!="NULL"&& parseInt(topsNum)>=parseInt(topFrom)&&parseInt(topsNum)>=parseInt(topTo)&&parseInt(topFrom)!=parseInt(topTo)){
    return true}
  else {
    return false}
}

function resetVars(){
topFrom = "NULL";
topTo = "NULL";
topsNum = "NULL";
}



function uploadData(event) {
  event.preventDefault();

  if(checkAllComponents()){
    if(loadOption=="file"){
      document.getElementById('file-input').click();
      upload_parameters();
      const element= document.getElementById("popup");
      element.style.visibility = "hidden";
      alert("Дані завантажено!") 
      clearVal()
    }
    else{
      upload_parameters();
      const element= document.getElementById("popup");
      element.style.visibility = "hidden";
      alert("Дані завантажено!")
      clearVal()
    }
  }
  else {
    alert ("Дані введено некоректно. Перевірте!")
  }
}


function uploadFile(event){
  var inputId = event.target.id;
  const files = document.getElementById(inputId);
  const formData = new FormData()
  formData.append("file", files.files[0], files.files[0].name)
  formData.append("topFrom", topFrom);
  axios.post("http://localhost:30501/upload_files", formData)
}

function upload_parameters(){
  axios.post('http://localhost:30501/upload_parameters', {
  "loadOption": loadOption,
  "topFrom": topFrom,
  "topTo": topTo,
  "topsNum": topsNum
  });
}
