/// <reference path="TreeNode.ts" />

class BleHub extends TreeNode  {
    constructor() {
        super()
        this.Update = this.update;
    }

    private update(): void {
        var bleNode: BleNode = new BleNode();
        bleNode.Name = 'Полевое устройство 1';
        this.Append(bleNode);

        bleNode = new BleNode();
        bleNode.Name = 'Полевое устройство 2';
        this.Append(bleNode);

        bleNode = new BleNode();
        bleNode.Name = 'Полевое устройство 3';
        this.Append(bleNode);
    }


    public GetScan() {

    }

    public GetNode() {

    }
}
