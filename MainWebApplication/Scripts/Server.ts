
class Server extends HTMLLIElement {
    constructor() {
        super();
        // <span class="caret caret-down" > Сервер < /span>
        var name: HTMLSpanElement = new HTMLSpanElement();
        name.className = 'caret';
        name.textContent = 'Сервер';
        this.appendChild(name);

        // <ul class="nested active" >
        var nodes: HTMLUListElement = new HTMLUListElement();
        nodes.className = 'nested';
        this.appendChild(nodes);
        //<span class="caret BleSensor" data = "полевое устройство" > Полевое устройство 1 < /span>

/*
            */

        this.addEventListener('click', this.OnClick);



    }

    private OnClick(): void {
        this.parentElement
            .querySelector(".nested")
            .classList.toggle("active");
        this.classList.toggle("caret-down");
    }
}
