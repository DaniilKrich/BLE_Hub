using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Text.Json;
using System.Collections;

namespace MainWebApplication
{
    public class BleServices : List<BleService>
    {


        /*
         [
    {
        "resultList": [
            {
                "channelType": "",
                "duration": "2:29:30",
                "episodeno": 0,
                "genre": "Drama",
                "genreList": [
                    "Drama"
                ],
                "genres": [
                    {
                        "personName": "Drama"
                    }
                ],
                "id": 1204,
                "language": "Hindi",
                "name": "The Great Target",
                "productId": 1204,
                "productMasterId": 1203,
                "productMasterName": "The Great Target",
                "productName": "The Great Target",
                "productTypeId": 1,
                "productTypeName": "Movie",
                "rating": 3,
                "releaseyear": "2005",
                "showGoodName": "Movies ",
                "views": 8333
            },
            {
                "channelType": "",
                "duration": "2:30:30",
                "episodeno": 0,
                "genre": "Romance",
                "genreList": [
                    "Romance"
                ],
                "genres": [
                    {
                        "personName": "Romance"
                    }
                ],
                "id": 1144,
                "language": "Hindi",
                "name": "Mere Sapnon Ki Rani",
                "productId": 1144,
                "productMasterId": 1143,
                "productMasterName": "Mere Sapnon Ki Rani",
                "productName": "Mere Sapnon Ki Rani",
                "productTypeId": 1,
                "productTypeName": "Movie",
                "rating": 3,
                "releaseyear": "1997",
                "showGoodName": "Movies ",
                "views": 6482
            },
            {
                "channelType": "",
                "duration": "2:34:07",
                "episodeno": 0,
                "genre": "Drama",
                "genreList": [
                    "Drama"
                ],
                "genres": [
                    {
                        "personName": "Drama"
                    }
                ],
                "id": 1520,
                "language": "Telugu",
                "name": "Satyameva Jayathe",
                "productId": 1520,
                "productMasterId": 1519,
                "productMasterName": "Satyameva Jayathe",
                "productName": "Satyameva Jayathe",
                "productTypeId": 1,
                "productTypeName": "Movie",
                "rating": 3,
                "releaseyear": "2004",
                "showGoodName": "Movies ",
                "views": 9910
            }
        ],
        "resultSize": 1171,
        "pageIndex": "1"
    }
]
         
         */
        public BleServices(string json)
        {
            var tmp = JsonSerializer.Deserialize<List<BleService>>(json);
            this.AddRange(tmp);
        }
    }
}
