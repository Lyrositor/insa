/* --- Collect'IF Client Application --- */

/* Angular Material */
var collectIFClientApp = angular.module('CollectIFClientApp', ['ngMaterial', 'ngMessages']);

/* Index Controller */
collectIFClientApp.controller('ClientIndexController', function ($scope, $http) {
  /* $http.get('phones/phones.json').success(function(data) {
    $scope.phones = data;
  });

  $scope.orderProp = 'age'; */
  
  var user = this;
  user.email = '';
  
  user.submit = function() {
    console.log('Submit start');
    $.ajax({
      url: './ActionServlet',
      type: 'POST',
      data: {
        action: 'listeActivite',
        email: user.email
      },
      dataType: 'json'
    })
      .done(function (data) {
        console.log(data);
        var adherent = data;
        /*var contenuHtml = '<ul>';
        var i;
        for (i = 0; i < activites.length; i++) {
          contenuHtml += '<li>' + activites[i].denomination + '</li>';
        }
        contenuHtml += '</ul>';
        $('#listeActivites').html(contenuHtml);*/
      })
      .fail(function (e) {
        console.log(e);
        /*$('#listeActivites').html('ERREUR de chargement');*/
      })
      .always(function () {
        console.log('Submit end');
        //
      });
    };
});

/* Inscription Controller */
collectIFClientApp.controller('ClientInscriptionController', function ($scope, $http) {
  
});

/* Demandes Controller */
collectIFClientApp.controller('ClientDemandesController', function ($scope, $http) {
  $scope.date = new Date();
});