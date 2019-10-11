export enum E_PC_TO_TGT_CODE {
    IS_ALIVE_REQUEST_CODE			= 1,
	WRITE_PCI_REQUEST_CODE			= 2,
	READ_PCI_REQUEST_CODE			= 3,
}

export class HeaderRequest  {
    Magic : number;
    Code : E_PC_TO_TGT_CODE;
    Length : number;
    Checksum : number;
}

export class HeaderReply {
    Magic : number;
    Code : number;
    Length : number;
    Checksum : number;
}
