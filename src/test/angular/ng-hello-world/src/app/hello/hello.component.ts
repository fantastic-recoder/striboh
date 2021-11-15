import { ThrowStmt } from '@angular/compiler';
import { Component, OnInit } from '@angular/core';
import { HelloService } from '../org/striboh/hello.service';

@Component({
  selector: 'app-hello',
  templateUrl: './hello.component.html',
  styleUrls: ['./hello.component.styl']
})
export class HelloComponent implements OnInit {
  
  m_TextToSend:string = "";
  m_ServerReturned = "No answer yet."

  constructor(private m_HelloService: HelloService) { }

  ngOnInit(): void {
  }

  sendToServer() : void {
    console.log("--> send to server:"+this.m_TextToSend+".");
    this.m_HelloService.echo(this.m_TextToSend,(p_Reply:string)=>{ this.onReceived(p_Reply);} );
  }

  onReceived(pMessage:string) {
    this.m_ServerReturned = pMessage;
    console.log("--> received from server:'"+this.m_ServerReturned+"'.");
  }

  updateTextToSend(pValue:string):void {
    this.m_TextToSend = pValue;
  }
}
