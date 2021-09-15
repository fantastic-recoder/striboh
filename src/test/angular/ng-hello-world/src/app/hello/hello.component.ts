import { ThrowStmt } from '@angular/compiler';
import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-hello',
  templateUrl: './hello.component.html',
  styleUrls: ['./hello.component.styl']
})
export class HelloComponent implements OnInit {
  
  mTextToSend:string = "";

  constructor() { }

  ngOnInit(): void {
  }

  sendToServer() : void {
    console.log("--> send to server:"+this.mTextToSend+".");
  }

  updateTextToSend(pValue:string):void {
    this.mTextToSend = pValue;
    console.log("<-> updateTextToSend("+this.mTextToSend+").");
  }
}
