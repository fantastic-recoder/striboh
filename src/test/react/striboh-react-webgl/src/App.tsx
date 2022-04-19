import React from 'react';
import logo from './logo.svg';
import './App.css';
import Glediator from './glediator/Glediator';

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <p>
          Striboh React demonstrator.
        </p>
      </header>
      <Glediator/>
    </div>
  );
}

export default App;
