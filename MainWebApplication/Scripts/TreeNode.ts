﻿/// <reference path="TreeElement.ts" />

class TreeNode extends TreeElement {
   

    constructor(
    ) {
        super();
        this.children = [];

        this.nodeWrapper = <HTMLLIElement>document.createElement('li');
        this.title.className = 'caret';
        this.nodeWrapper.appendChild(this.title);

        // <ul class="nested active" >
        this.container = <HTMLUListElement>document.createElement('ul');
        this.container.className = 'nested';
        this.nodeWrapper.appendChild(this.container);

        this.OnClick = this.onClick;
    }

   

  
    public Append(node: TreeElement): void {
        node.parent = this;
        this.children.push(node);
        this.container.appendChild(node.Node);
    }

    private onClick(this: HTMLSpanElement, ev: MouseEvent): void {
        this.parentElement
            .querySelector(".nested")
            .classList.toggle("active");

        this.classList.toggle("caret-down");
    }

   

}