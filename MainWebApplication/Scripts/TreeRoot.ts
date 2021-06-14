class TreeRoot extends TreeElement {


    constructor(
        parentContainer: HTMLElement
    ) {
        super();
        this.children = [];
        this.nodeWrapper = parentContainer;
        this.nodeWrapper.appendChild(this.title);

        // <ul class="nested active" >
        this.container = <HTMLUListElement>document.createElement('ul');
        this.container.className = 'nested active';
        this.nodeWrapper.appendChild(this.container);

        //this.OnClick = this.onClick;
    }

    public Append(node: TreeElement): void {
        node.parent = this;
        this.children.push(node);
        this.container.appendChild(node.Node);
    }


    //private onClick(this: HTMLSpanElement, ev: MouseEvent): void {

    //    console.log(this);

        
    //    //this.parentElement
    //    //    .querySelector(".nested")
    //    //    .classList.toggle("active");

    //    //this.classList.toggle("caret-down");
    //}

}