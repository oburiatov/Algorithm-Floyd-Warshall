import logo from './logo.svg';
import './App.css';
import * as go from "gojs";
import React, { Component } from "react";


class Sidebar extends React.Component {
  state = {};
  hideWindow = () => {
    const element= document.getElementById("popup");
    if (element)
    {
      element.style.visibility = "hidden";
    }
  }

}


function App() {
  return (
    <div className='main'>
      <div className='side-bar'>
        <nav>
        <button className='side-bar-button'>Завантажити дані</button>
        <button className='side-bar-button'>Відобразити дані</button>
        <button className='side-bar-button'>Зберегти</button>

        <marquee>Text</marquee>
        </nav>
      </div>

      <div className='popup' id='popup'>
        <div className='popup__body'>
          <div className='popup__content'>
            <div className='radiobuttons'>
              <label for="loadRadioId" className="radio">
                <input type="radio" name="radioField" id="loadRadioId" class="radio__input"></input>
                <div className='radio__radio'></div>
                Завантажити з файла
              </label>
              <label for="loadRadioId2" className="radio">
                <input type="radio" name="radioField" id="loadRadioId2" class="radio__input"></input>
                <div className='radio__radio'></div>
                Згенерувати
              </label>
            </div>
            <div className='popup__text'>
              <label id='text__topsnum'>Кількість вершин</label>
              <input type='text' id='field__topsnum'></input>
            </div>
            <div className='popup__text'>
              <label id='text__topfrom'>Пошук з вершини</label>
              <input type='text' id='field__topfrom'></input>
            </div>
            <div className='popup__text'>
              <label id='text__topto'>Пошук до вершини</label>
              <input type='text' id='field__topto'></input>
            </div>
            <button className='side-bar-button' id='run-button'>Запустити програму</button>
            <button className='side-bar-button' onClick={this.hideWindow()}>Вийти</button>
          </div>
        </div>
      </div>

      
    </div>
  )

}

export default App;


// function changeVisibility() {
//   const element= document.getElementById("popup");
//   if (element)
//   {
//     element.style.visibility = "hidden";
//   }
  
// }