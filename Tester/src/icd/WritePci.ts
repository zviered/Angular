import {HeaderRequest} from '../icd/Header'
import {HeaderReply} from '../icd/Header'
import {E_PC_TO_TGT_CODE} from '../icd/Header'

export class WritePciRequest
{
    constructor (){
        this.Header = new HeaderRequest;
        this.Header.Magic = 7;
        this.Header.Code = E_PC_TO_TGT_CODE.WRITE_PCI_REQUEST_CODE;
        this.Header.Length = 0;
        this.Header.Checksum = 0;
    }
    Header: HeaderRequest;
    Bar : number;
    Offset: number;
    Data: number;
}

export type MyArray ={
    y:number;
}
/***************************************************** */
export class WritePciReply {
    Header: HeaderReply;
 }
