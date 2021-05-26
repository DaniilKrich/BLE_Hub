/// <reference path="TreeElement.ts" />

class TreeLeaf extends TreeElement {
    constructor(
    ) {
        super();
        this.children = [];

        this.nodeWrapper = <HTMLLIElement>document.createElement('li');
        this.title.className = 'Characteristic';
        this.nodeWrapper.appendChild(this.title);
       
        var t: TreeLeaf = this;

        this.OnClick = () => t.onClick();
    }

    private onClick(): void {
        var msg: string = ': ok!';
        alert(this.Name+msg);
    }
}
