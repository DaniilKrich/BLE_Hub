/// <reference path="TreeRoot.ts" />

class Server extends TreeRoot {
    private AddBleHubButton: HTMLDivElement = document.createElement('div') as HTMLDivElement;
    private AddBleHubForm: HTMLFormElement = document.createElement('form');


    constructor(
        parentContainer: HTMLElement
    ) {
        super(parentContainer);

        this.AddBleHubButton.className = 'Action';
        this.AddBleHubButton.classList.add('Clickable');
        this.AddBleHubButton.innerText = 'Добавление концентратора';
        this.AddBleHubButton.onclick = () => this.AddBleHubButtonOnclick();


        // <form >
        //    <div class="form-group">
        //    </div>

        //<input name="__RequestVerificationToken"
        //type="hidden"
        //value="CfDJ8PrUNlfFZ9tAh7ylCV1SUXOTUxRGeEysMlr1-0wggkc0CDm_oVujbo2VLfGxSmfRnkFkRwBMwzIuxHRphcLlT69xWrh_O5dUtQdunI4uBhs26IkpCNaAQpBtA8kWCj9-kzi9pYVomuU7v4s-47Wnbx0"></form>


        this.AddBleHubForm.innerHTML =
            '<div class="form-group">\
                <label class="control-label" for="Name">Сетевое имя</label>\
                <input class="form-control" type="text" id="Name" name="Name" value="">\
                <span class="text-danger field - validation - valid" data-valmsg-for="Name" data-valmsg-replace="true">\
                </span>\
            </div>\
            <input type="submit" value="Добавить" class="btn btn-primary">';

        //        <input type="submit" value="Добавить" class="btn btn-primary">
        //var submit: HTMLInputElement = document.createElement('input');
        //submit.className = 'btn';
        //submit.classList.add('btn-primary');
        //submit.onclick = () => this.CreateBleHub();
        //this.AddBleHubForm.appendChild(submit);

        var cr = () => this.CreateBleHub();

        this.AddBleHubForm.addEventListener("submit", (event) => {
            event.preventDefault();
            cr();
        });

        this.Update = this.update;
        this.OnClick = () => this.showActions();
    }

    private updateReqListener(req: XMLHttpRequest) {
        //var bleHub: BleHub = new BleHub();
        //bleHub.Name = 'Концентратор 1';
        //this.Append(bleHub);

        do {
            var tmp = this.children.pop()
        }while (this.children.length > 0);

        this.container.innerHTML = '';


        var json: IBleHub[] = JSON.parse(req.response) as IBleHub[];

        for (var hub in json) {
            var bleHub: BleHub = new BleHub(json[hub]);
            this.Append(bleHub);
        }


    }

    private update(): void {

        var xhr: XMLHttpRequest = new XMLHttpRequest();
        xhr.onload = () => this.updateReqListener(xhr);
        xhr.open('get', '/BleHubs/GetList', true);
        xhr.send();
        //bleHub = new BleHub();
        //bleHub.Name = 'Концентратор 2';
        //this.Append(bleHub);

        //var bleHub: BleHub = new BleHub();
        //bleHub.Name = 'Концентратор 3';
        //this.Append(bleHub);
    }

    private showActions(): void {
        console.log(this);
        actions.innerHTML = '';
        interfaceZone.innerHTML = '';
        var header: HTMLHeadElement = document.createElement('h1');
        header.textContent = this.Name;
        actions.append(header);
        actions.append(this.AddBleHubButton);
    }




    private AddBleHubButtonOnclick(): void {
        interfaceZone.innerHTML = '';
        interfaceZone.append(this.AddBleHubForm);
    }


    private CreateBleHubReqListener(req: XMLHttpRequest) {
        interfaceZone.innerHTML = req.responseText;
        this.Update();
    }

    private CreateBleHub() {
        var xhr: XMLHttpRequest = new XMLHttpRequest();
        var fd = new FormData(this.AddBleHubForm);
        xhr.onload = () => this.CreateBleHubReqListener(xhr);
        //action = "/BleHubs/Create" method = "post"
        xhr.open('post', '/BleHubs/CreateFnc', true);
        xhr.send(fd);
        //xhr.setRequestHeader();
    }


}




