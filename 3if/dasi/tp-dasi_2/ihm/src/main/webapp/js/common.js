var CLE_API = 'AIzaSyDcVVJjfmxsNdbdUYeg9MjQoJJ6THPuap4';

var PIN_URL = 'http://chart.apis.google.com/chart?chst=d_map_pin_letter&chld=%E2%80%A2|';

var SERVER = '/ihm/ActionServlet';

function sendRequest($http, action, params, success, error) {
    if (params)
        params.action = action;
    else
        params = {action: action};
    $http({
        method: 'POST',
        url: SERVER,
        params: params
    }).then(function (response) {
        //console.log(response);
        if (success)
            success(response.data);
    }, function (response) {
        if (error)
            error(response.data);
    });
}

/*
 * Source: http://stackoverflow.com/questions/5448545/how-to-retrieve-get-parameters-from-javascript
 */
function getSearchParameters() {
      var prmstr = window.location.search.substr(1);
      return prmstr != null && prmstr != "" ? transformToAssocArray(prmstr) : {};
}

/*
 * Source: http://stackoverflow.com/questions/5448545/how-to-retrieve-get-parameters-from-javascript
 */
function transformToAssocArray( prmstr ) {
    var params = {};
    var prmarr = prmstr.split("&");
    for ( var i = 0; i < prmarr.length; i++) {
        var tmparr = prmarr[i].split("=");
        params[tmparr[0]] = tmparr[1];
    }
    return params;
}