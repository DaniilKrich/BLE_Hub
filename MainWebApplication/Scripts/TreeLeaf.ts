
class TreeLeaf extends TreeElement {
    constructor(
    ) {
        super();
        this.children = [];

        this.nodeWrapper = <HTMLLIElement>document.createElement('li');
        this.nodeWrapper.appendChild(this.title);
       
        this.OnClick = this.onClick;
    }

    private onClick(this: HTMLSpanElement, ev: MouseEvent): void {
        this.parentElement
            .querySelector(".nested")
            .classList.toggle("active");

        this.classList.toggle("caret-down");
    }
}
