/// <reference path="IBleHub.ts" />
/// <reference path="IBleService.ts" />
interface IBleServer {
    "bleServerID": number;
    "bleHub": IBleHub;
    "bleServices": IBleService[];
    "bleAdr": string;
    "name": string;
}
