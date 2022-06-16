import logo from './logo.svg';
import './App.css';
import axios from 'axios';
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
              const element = document.getElementById("popup");
              element.style.visibility = "visible";
              resetVars()
            }}>
            Завантажити дані</button>
          <button className='side-bar-button'
            onClick={(event) => processData(event)}>Запустити програму</button>
          <button className='side-bar-button' onClick={clearSVGField}>Очистити поле</button>

          <marquee>Text</marquee>
        </nav>


      </div>
      <div id="myDiagramDiv">
        <svg width="960" height="600" id="svgdiagram"></svg>
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
              onClick={(event) => uploadData(event)}
            >Завантажити</button>
            <button className='side-bar-button'
              onClick={() => {
                const element = document.getElementById("popup");
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




function clearSVGField() {
  document.getElementById("svgdiagram").innerHTML = "";
}

function processData(event) {

  clearSVGField();
  //   var graphData = {
  //     nodes: [{ name: "A",fix: "123" }, { name: "B",fix: "123" }, { name: "C",fix: "123" }, { name: "D",fix: "123" }],
  //     links: [
  //       { source: "A", target: "B",color: "red" },
  //       { source: "B", target: "C",color: "yellow" },
  //       { source: "D", target: "C",color: "black" }
  //     ]
  //   };


  var links = [{ source: "A", target: "B", value: "1.2", color: "red" },
  { source: "B", target: "C", value: "2000", color: "red" },
  { source: "D", target: "C", value: "1.2", color: "black" }]

  //[{"source":"Harry","target":"Sally","value":"1.2"},{"source":"Harry","target":"Mario","value":"1.3"},{"source":"Sarah","target":"Alice","value":"0.2"},{"source":"Eveie","target":"Alice","value":"0.5"},{"source":"Peter","target":"Alice","value":"1.6"},{"source":"Mario","target":"Alice","value":"0.4"},{"source":"James","target":"Alice","value":"0.6"},{"source":"Harry","target":"Carol","value":"0.7"},{"source":"Harry","target":"Nicky","value":"0.8"},{"source":"Bobby","target":"Frank","value":"0.8"},{"source":"Alice","target":"Mario","value":"0.7"},{"source":"Harry","target":"Lynne","value":"0.5"},{"source":"Sarah","target":"James","value":"1.9"},{"source":"Roger","target":"James","value":"1.1"},{"source":"Maddy","target":"James","value":"0.3"},{"source":"Sonny","target":"Roger","value":"0.5"},{"source":"James","target":"Roger","value":"1.5"},{"source":"Alice","target":"Peter","value":"1.1"},{"source":"Johan","target":"Peter","value":"1.6"},{"source":"Alice","target":"Eveie","value":"0.5"},{"source":"Harry","target":"Eveie","value":"0.1"},{"source":"Eveie","target":"Harry","value":"2.0"},{"source":"Henry","target":"Mikey","value":"0.4"},{"source":"Elric","target":"Mikey","value":"0.6"},{"source":"James","target":"Sarah","value":"1.5"},{"source":"Alice","target":"Sarah","value":"0.6"},{"source":"James","target":"Maddy","value":"0.5"},{"source":"Peter","target":"Johan","value":"0.7"}];




  var nodes = {};

  // Compute the distinct nodes from the links.
  links.forEach(function (link) {
    link.source = nodes[link.source] ||
      (nodes[link.source] = { name: link.source });
    link.target = nodes[link.target] ||
      (nodes[link.target] = { name: link.target });
    link.value = +link.value;
  });

  var width = 960,
    height = 700;

  //d3.layout.force()
  var force = d3
    .layout.force()
    .nodes(d3.values(nodes))
    .links(links)
    .size([width, height])
    .linkDistance(100)
    .charge(-300)
    .on("tick", tick)
    .start();

  var svg = d3.select("svg").append("svg")
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
    .attr("markerWidth", 10)
    .attr("markerHeight", 10)
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

  var text = pg.append("text").style("font-weight", "bold").style("font", "13px times").style("fill", function (d) {
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
    .attr("r", 10);

  // add the text 
  node.append("text")
    .attr("x", 12)
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


// function processData(event){
//   //initilize svg or grab svg
//   var svg = d3.select("svg");
//   var width = svg.attr("width");
//   var height = svg.attr("height");

//   var graphData = {
//     nodes: [{ name: "A",fix: "123" }, { name: "B",fix: "123" }, { name: "C",fix: "123" }, { name: "D",fix: "123" }],
//     links: [
//       { source: "A", target: "B",color: "red" },
//       { source: "B", target: "C",color: "yellow" },
//       { source: "D", target: "C",color: "black" }
//     ]
//   };

//   var simulation = d3
//   .forceSimulation(graphData.nodes)
//   .force("charge", d3.forceManyBody().strength(-30))
//   .force("center", d3.forceCenter(width / 2, height / 2))
//   .force("link", d3.forceLink(graphData.links).id(d => d.name))
//   .force("link",d3.forceLink(graphData.links).distance(100))

//   .on("tick", ticked);

//   let link = svg.selectAll(".linkLine").data(graphData.links);


//   var links = svg
//     .append("g")
//     .attr('marker-start', "url(#arrow)")

//     .selectAll("line")
//     .data(graphData.links)
//     .enter()
//     .append("g")
//     .append("line")
//     .attr("stroke-width", 3)
//     .attr("height", 30)



//     ;

//   var drag = d3
//     .drag()
//     .on("start", dragstarted)
//     .on("drag", dragged)
//     .on("end", dragended);

//    let arrow= svg.append("svg:defs").append("svg:marker")
//     .attr("id", "arrow")
//     .attr("viewBox", "0 -5 10 10")
//     .attr('refX', -93) //so that it comes towards the center.
//     .attr("markerWidth", 3)
//     .attr("markerHeight", 3)
//     .attr("orient", "auto")
//     .append("svg:path")
//     .attr("d", "M0,-5L10,0L0,5");    



//   var textsAndNodes = svg
//     .append("g")
//     .style("font", "10px times")
//     .selectAll("g")
//     .data(graphData.nodes)
//     .enter()
//     .append("g")
//     .call(drag);




//   var circles = textsAndNodes
//     .append("circle")
//     .attr("r", 10)
//     .attr("fill", "red");

//   var texts = textsAndNodes.append("text").text(function(d) {
//     return d.name;
//   });


//   function ticked1() {


//   }



//   function ticked() {
//     //translate(x, y)
//     textsAndNodes.attr("transform", function(d) {
//       return "translate(" + d.x + ", " + d.y + ")";
//     });

//     links
//       .attr("x1", function(d) {
//         // textsAndNodes.attr("transform", "translate(" + 500 + ", " + 450 + ")");
//         return d.source.x;
//       })
//       .attr("y1", function(d) {
//         return d.source.y;
//       })
//       .attr("x2", function(d) {
//         return d.target.x;
//       })
//       .attr("y2", function(d) {
//         return d.target.y;
//       })
//       .style("stroke", function(d) {
//         return d.color;
//       })


//     // console.log(simulation.alpha());
//     // console.log(graphData.links.source);


//   }

//   function dragstarted(d) {
//     //your alpha hit 0 it stops! make it run again
//     simulation.alphaTarget(0.3).restart();
//     d.fx = event.x;
//     d.fy = event.y;
//   }
//   function dragged(d) {
//     d.fx = event.x;
//     d.fy = event.y;
//   }

//   function dragended(d) {
//     // alpha min is 0, head there
//     simulation.alphaTarget(0);
//     d.fx = null;
//     d.fy = null;
//   }
// }

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
}



function uploadData(event) {
  event.preventDefault();

  if (checkAllComponents()) {
    if (loadOption == "file") {
      document.getElementById('file-input').click();
      upload_parameters();
      const element = document.getElementById("popup");
      element.style.visibility = "hidden";
      alert("Дані завантажено!")
      clearVal()
    }
    else {
      upload_parameters();
      const element = document.getElementById("popup");
      element.style.visibility = "hidden";
      alert("Дані завантажено!")
      clearVal()
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
    "loadOption": loadOption,
    "topFrom": topFrom,
    "topTo": topTo,
    "topsNum": topsNum
  });
}
