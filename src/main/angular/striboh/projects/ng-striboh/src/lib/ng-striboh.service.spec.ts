import { TestBed } from '@angular/core/testing';

import { NgStribohService } from './ng-striboh.service';

describe('NgStribohService', () => {
  let service: NgStribohService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(NgStribohService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
