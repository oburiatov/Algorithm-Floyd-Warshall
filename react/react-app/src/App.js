import logo from './logo.svg';
import './App.css';
import * as go from "gojs";
import React, { Component } from "react";
import { exec } from 'child_process';

let loadOption = "gen";
let topFrom = "NULL";
let topTo = "NULL";
let topsNum = "NULL";


// class Sidebar extends React.Component {
//   state = {};
//   hideWindow = () => {
//     const element= document.getElementById("popup");
//     if (element)
//     {
//       element.style.visibility = "hidden";
//     }
//   }

// }


function App() {
  return (
    <div className='main'>
      <div className='side-bar'>
        <nav>
        <button className='side-bar-button'
          onClick={() => {
            const element= document.getElementById("popup");
            element.style.visibility = "visible";
          }}>
            Завантажити дані</button>
        <button className='side-bar-button'>Відобразити результат</button>
        <button className='side-bar-button'>Зберегти зображення</button>

        <marquee>Text</marquee>
        </nav>
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
            <input id="file-input" type="file" name="name"></input>
            <button className='side-bar-button' id='run-button'
              onClick={() => processData()}
              >Запустити програму</button>
            <button className='side-bar-button' 
              onClick={() => {
                const element= document.getElementById("popup");
                element.style.visibility = "hidden";
              }}>Вийти</button>
          </div>
        </div>
      </div>

      
    </div>
  )

}

export default App;


function processData(){
  if(checkAllComponents()){
    if(loadOption=="file"){
      document.getElementById('file-input').click();
    }

    const execSync = require('child_process').execSync;
    execSync("ls -la", (error, stdout, stderr) => {
      if (error) {
          console.log(`error: ${error.message}`);
          return;
      }
      if (stderr) {
          console.log(`stderr: ${stderr}`);
          return;
      }
      console.log(`stdout: ${stdout}`);
    });
  }
  else {
    alert ("Дані введено некоректно. Перевірте!")
    alert (loadOption)
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
  if(topsNum!="NULL"&&topFrom!="NULL"&&topTo!="NULL"){return true}
  else {return false}
}
