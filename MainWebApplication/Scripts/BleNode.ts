/// <reference path="TreeNode.ts" />

class BleNode extends TreeNode {
    constructor() {
        super();
        this.Update = this.update;
    }

    private update(): void {
        var bleService: BleService = new BleService();
        bleService.Name = 'Почва';
        this.Append(bleService);

        bleService = new BleService();
        bleService.Name = 'Атмосфера';
        this.Append(bleService);
    }
}
