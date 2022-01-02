import { ThrowStmt } from '@angular/compiler';
import { Component, OnInit } from '@angular/core';
import { NgServerService } from '../ng_server.service';

@Component({
  selector: 'app-hello',
  templateUrl: './hello.component.html',
  providers: [ { provide: 'mHostAndPort', useValue: '0.0.0.0:5600' }, ],
  styleUrls: ['./hello.component.styl'],
})
export class HelloComponent implements OnInit {

  mTextToSend = '';
  mServerReturned = 'No answer yet.'

  constructor(private mNgService: NgServerService ) { 
  }

  ngOnInit(): void {
  }

  sendToServer(): void {
    console.log('--> send to server:' + this.mTextToSend + '.');
    this.mNgService.echo(this.mTextToSend, ( pReply: string ) => { this.onReceived(pReply); } );
  }

  onReceived(pMessage: string): void {
    this.mServerReturned = pMessage;
    console.log('--> received from server:\'' + this.mServerReturned + '\'.');
  }

  updateTextToSend(pValue: string): void {
    this.mTextToSend = pValue;
  }
}
