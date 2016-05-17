/* --- Collect'IF Client Application --- */

/* Angular Material */
var collectIFClientApp = angular.module('CollectIFClientApp', ['ngMaterial', 'ngMessages']);

/* Index Controller */
collectIFClientApp.controller('ClientIndexController', ['$scope', '$http', '$mdToast', function ($scope, $http, $mdToast) {
  $scope.user = new Object();
  $scope.user.email = '';
  
  afficherErreur = function(description) {
    $mdToast.show(
      $mdToast.simple()
        .textContent('Erreur : ' + description)
        .position($scope.getToastPosition())
        .hideDelay(10000)
    );
    
    alert('Erreur : ' + description);
  };
  
  $scope.user.submit = function() {
    $http({
      method: 'POST',
      url: './ActionServlet',
      params: {
        action: 'authentification',
        email: $scope.user.email
      }
    }).then(function success(response) {
        console.log(response);
        var data = response.data;
        
        if (data.erreur) {
          afficherErreur(data.erreur);
        } else {
          alert('good');
        }
    }, function error(response) {
        console.log(response);
        afficherErreur('Connexion impossible.');
    });
  };
  
}]);

/* Inscription Controller */
collectIFClientApp.controller('ClientInscriptionController', ['$scope', '$http', function ($scope, $http) {
  
}]);

/* Demandes Controller */
collectIFClientApp.controller('ClientDemandesController', ['$scope', '$http', function ($scope, $http) {
  $scope.date = new Date();
}]);