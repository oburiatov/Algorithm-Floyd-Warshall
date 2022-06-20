import logo from './logo.svg';
import './App.css';
import axios from 'axios';
import * as d3 from 'd3';

let loadOption = "gen";
let topFrom = "NULL";
let topTo = "NULL";
let topsNum = "NULL";
let programType = "NULL";
let jsonData = "NULL";
let jsonRes = "NULL";

function App() {
  return (
    <div className='main'>
      <div className='side-bar'>
        <nav>
          <button className='side-bar-button'
            onClick={() => {
              const element = document.getElementById("popup");
              element.style.visibility = "visible";
              resetVars()
            }}>
            Завантажити дані</button>
          <button className='side-bar-button'
            onClick={(event) => processData(event, "data")}>Показати граф</button>
          <button className='side-bar-button'
            onClick={(event) => processData(event, "result")}>Показати найкоротший шлях</button>            
          <button className='side-bar-button' onClick={clearSVGField}>Очистити поле</button>
          <div id='spentTimer'></div>
        </nav>
        

      </div>
      <div id="myDiagramDiv">
        <svg width="900" height="1000" id="svgdiagram"></svg>
      </div>
      <div className='popup' id='popup'>
        <div className='popup__body'>
          <div className='popup__content'>
            <div className='radiobuttons'>
              <label htmlFor="loadRadioId" className="radio">
                <input type="radio" name="radioField" id="loadRadioId" className="radio__input"
                  onClick={() => {
                    loadOption = "file";
                  }}></input>
                <div className='radio__radio'></div>
                Завантажити з файлу
              </label>
              <label htmlFor="loadRadioId2" className="radio" >
                <input type="radio" name="radioField" id="loadRadioId2" className="radio__input" defaultChecked
                  onClick={() => {
                    loadOption = "gen";
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
              onClick={(event) => uploadData(event, "parallel")}
            >Паралельний алгоритм</button>
            <button className='side-bar-button' id='run-button'
              onClick={(event) => uploadData(event,"sequential")}
            >Послідовний алгоритм</button>
            <button className='side-bar-button'
              onClick={() => {
                const element = document.getElementById("popup");
                element.style.visibility = "hidden";
                clearVal()
              }}>Вийти</button>
          </div>
        </div>
      </div>
      <div className='popup' id='popup-wait'>
        <div className='popup__body'>
          <div className='popup__content'> Зачекайте ...
      </div>
      </div>
      </div>


    </div>
  )

}

export default App;




function clearSVGField() {
  document.getElementById("svgdiagram").innerHTML = "";
}

function processData(event, option) {
  clearSVGField();
  if(jsonData=="NULL"||jsonRes=="NULL")
  {
    alert("Ви не завантажили дані!")
  }
  else{
    var links;
    let rawdata;
    if(option=="data"){
      rawdata = jsonData;
      links = JSON.parse(JSON.stringify(rawdata));
    }
    else if(option=="result") {
      rawdata = jsonRes;
      links = JSON.parse(JSON.stringify(rawdata));
      document.getElementById("spentTimer").textContent = "Час роботи: "+links[links.length-1].time
    }
    

    
    links = links.slice(0,-1)

    var nodes = {};

    links.forEach(function (link) {
      link.source = nodes[link.source] ||
        (nodes[link.source] = { name: link.source });
      link.target = nodes[link.target] ||
        (nodes[link.target] = { name: link.target });
      link.value = +link.value;
    });

    var width = 900,
      height = 600;

    //d3.layout.force()
    var force = d3
      .layout.force()
      .nodes(d3.values(nodes))
      .links(links)
      .size([width, height])
      .linkDistance(200)
      .charge(-300)
      .on("tick", tick)
      .start();

    var svg = d3.select("#svgdiagram").append("svg")
      .attr("width", width)
      .attr("height", height);

    // build the arrow.
    svg.append("svg:defs").selectAll("marker")
      .data(["end"])      // Different link/path types can be defined here
      .enter().append("svg:marker")    // This section adds in the arrows
      .attr("id", String)
      .attr("viewBox", "0 -5 13 10")
      .attr("refX", 15)
      .attr("refY", -1.5)
      .attr("markerWidth", 15)
      .attr("markerHeight", 15)
      .attr("orient", "auto")
      .append("svg:path")
      .attr("d", "M0,-5L10,0L0,5")
      ;

    // add the links and the arrows
    var pg = svg.append("svg:g").selectAll("path")
      .data(force.links())
      .enter().append("g");

    var path = pg.append("path")
      .attr("class", "link")
      .attr("marker-end", "url(#end)");

    var text = pg.append("text").style("font-weight", "bold").style("font", "17px times").style("fill", function (d) {
      return d.color;
    }).text(function (d) {
      return d.value;
    });

    // define the nodes
    var node = svg.selectAll(".node")
      .data(force.nodes())
      .enter().append("g")
      .attr("class", "node")
      .call(force.drag);

    // add the nodes
    node.append("circle")
      .attr("r", 15);

    // add the text 
    node.append("text")
      .attr("x", 0)
      .attr("dy", "0.67em")
      .style("font", "15px times")
      .text(function (d) { return d.name; });

    // add lines
    function tick() {
      path.attr("d", function (d) {
        var dx = d.target.x - d.source.x,
          dy = d.target.y - d.source.y,
          dr = Math.sqrt(dx * dx + dy * dy);
        return "M" +
          d.source.x + "," +
          d.source.y + " L" +
          // dr + "," + dr + " 0 0,1 " + 
          d.target.x + "," +
          d.target.y;
      })
        .style("stroke", function (d) {
          return d.color;
        })

        ;

      text.attr("transform", function (d) {
        return "translate(" + ((d.source.x + d.target.x) / 2) + "," + ((d.source.y + d.target.y) / 2) + ")";
      });

      node
        .attr("transform", function (d) {
          return "translate(" + d.x + "," + d.y + ")";
        });
    }
}
}


function isNumber(event) {
  var clickedId = event.target.id;
  var inputedText = document.getElementById(clickedId).value;

  if (!validation.isNumber(inputedText)) {
    document.getElementById(clickedId).style.borderColor = "red";
    setVal(clickedId, "NULL");
  }
  else if (validation.moreThan(inputedText)) {
    document.getElementById(clickedId).style.borderColor = "red";
    setVal(clickedId, "NULL");
  }
  else {
    document.getElementById(clickedId).style.borderColor = "green";
    setVal(clickedId, inputedText);
  }
}

function setVal(clickedId, val) {
  if (clickedId == "field__topsnum") { topsNum = val }
  else if (clickedId == "field__topfrom") { topFrom = val }
  else if (clickedId == "field__topto") { topTo = val }
}

function clearVal() {
  document.getElementById("field__topsnum").value = ""
  document.getElementById("field__topfrom").value = ""
  document.getElementById("field__topto").value = ""
}

var validation = {
  isNotEmpty: function (str) {
    var pattern = /\S+/;
    return pattern.test(str);  // returns a boolean
  },
  isNumber: function (str) {
    var pattern = /^\d+\.?\d*$/;
    return pattern.test(str);  // returns a boolean
  },
  moreThan: function (str) {
    if (Number(str) > 1000) { return true }
    else return false;
  }
};

function checkAllComponents() {
  if (topsNum != "NULL" && topFrom != "NULL" && topTo != "NULL" && parseInt(topsNum) >= parseInt(topFrom) && parseInt(topsNum) >= parseInt(topTo) && parseInt(topFrom) != parseInt(topTo)) {
    return true
  }
  else {
    return false
  }
}

function resetVars() {
  topFrom = "NULL";
  topTo = "NULL";
  topsNum = "NULL";
  programType = "NULL";
}



function uploadData(event, state) {
  event.preventDefault();

  if (checkAllComponents()) {
    if (loadOption == "file") {
      document.getElementById('file-input').click();
      programType = state;
      upload_parameters();
      const element = document.getElementById("popup");
      element.style.visibility = "hidden";
      clearVal()
      exec()
      
    }
    else {
      programType = state;
      upload_parameters();
      const element = document.getElementById("popup");
      element.style.visibility = "hidden";
      clearVal()
      exec()
    }
  }
  else {
    alert("Дані введено некоректно. Перевірте!")
  }
}


function uploadFile(event) {
  var inputId = event.target.id;
  const files = document.getElementById(inputId);
  const formData = new FormData()
  formData.append("file", files.files[0], files.files[0].name)
  formData.append("topFrom", topFrom);
  axios.post("http://localhost:30501/upload_files", formData)
}

function upload_parameters() {
  axios.post('http://localhost:30501/upload_parameters', {
    "programType": programType,
    "loadOption": loadOption,
    "topFrom": topFrom,
    "topTo": topTo,
    "topsNum": topsNum
  });
}

function download_data() {
  // const FileDownload = require('js-file-download');
  axios({
    url: 'http://localhost:30501/download_data', 
    method: 'GET',
    responseType: 'json', 
}).then((response) => {
  jsonData = JSON.parse(JSON.stringify(response.data));
})
}

function download_res() {
  // const FileDownload = require('js-file-download');
  axios({
    url: 'http://localhost:30501/download_res', 
    method: 'GET',
    responseType: 'json', 
}).then((response) => {
  jsonRes = JSON.parse(JSON.stringify(response.data));
})
}

function exec() {
  const element = document.getElementById("popup-wait");
  element.style.visibility = "visible";
  // const FileDownload = require('js-file-download');
  axios({
    url: 'http://localhost:30501/run', 
    method: 'GET',
    responseType: 'json', 
}).then((response) => {
  element.style.visibility = "hidden";
  alert("Програма відпрацювала успішно. Можете переглянути результат")
  download_data()
  download_res()
  console.log(response.data)
  })
}