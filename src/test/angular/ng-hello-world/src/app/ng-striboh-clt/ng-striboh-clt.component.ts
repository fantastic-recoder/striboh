import { ThrowStmt } from '@angular/compiler';
import { Component, OnInit } from '@angular/core';
import { NgServerService } from '../ng_server.service';

@Component({
  selector: 'app-ng-striboh-clt',
  templateUrl: './ng-striboh-clt.component.html',
  styleUrls: ['./ng-striboh-clt.component.styl'],
})
export class NgStribohCltComponent implements OnInit {

  mTextToSend = '';
  mServerReturned = 'No answer yet.';
  mP0 = 0;
  mP1 = 0;
  mAddResult = 0;

  constructor(private mNgService: NgServerService ) {
  }

  ngOnInit(): void {
  }

  sendEchoToServer(): void {
    console.log('--> send echo to server:' + this.mTextToSend + '.');
    this.mNgService.echo(this.mTextToSend, ( pReply: string ) => { this.onEchoReceived(pReply); } );
  }

  sendAddToServer(): void {
    console.log('--> send add to server:' + this.mP0 + ' + ' + this.mP1 + '.');
    this.mNgService.add(this.mP0, this.mP1, ( pReply: number ) => { this.onAddReceived(pReply); } );
  }

  updateP0ToSend(pP0: string): void {
    this.mP0 = parseInt(pP0, 10 );
    console.log('--> updated add values:' + this.mP0 + ' + ' + this.mP1 + '.');
  }

  updateP1ToSend(pP1: string): void {
    this.mP1 = parseInt( pP1, 10 );
    console.log('--> updated add values:' + this.mP0 + ' + ' + this.mP1 + '.');
  }

  sendShutdownToServer() : void {
    console.log('--> send shutdown to server:' + this.mTextToSend + '.');
    this.mNgService.shutdown(() => { console.log('Shutdown completed.') } );
  }

  onAddReceived(pAddResult: number): void {
    this.mAddResult = pAddResult;
    console.log('--> received add result from server:\'' + this.mAddResult + '\'.');

  }

  onEchoReceived(pMessage: string): void {
    this.mServerReturned = pMessage;
    console.log('--> received echo from server:\'' + this.mServerReturned + '\'.');
  }

  updateTextToSend(pValue: string): void {
    this.mTextToSend = pValue;
  }
}
