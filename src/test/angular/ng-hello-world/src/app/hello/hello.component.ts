import { ThrowStmt } from '@angular/compiler';
import { Component, OnInit } from '@angular/core';
import { HelloService } from '../org/striboh/hello.service';

@Component({
  selector: 'app-hello',
  templateUrl: './hello.component.html',
  styleUrls: ['./hello.component.styl']
})
export class HelloComponent implements OnInit {

  mTextToSend = '';
  mServerReturned = 'No answer yet.'

  constructor(private mHelloService: HelloService) { }

  ngOnInit(): void {
  }

  sendToServer(): void {
    console.log('--> send to server:' + this.mTextToSend + '.');
    this.mHelloService.echo(this.mTextToSend, ( pReply: string ) => { this.onReceived(pReply); } );
  }

  onReceived(pMessage: string): void {
    this.mServerReturned = pMessage;
    console.log('--> received from server:\'' + this.mServerReturned + '\'.');
  }

  updateTextToSend(pValue: string): void {
    this.mTextToSend = pValue;
  }
}
