var CollectIFAdminApp = angular.module('CollectIFAdminApp', ['ngMaterial', 'md.data.table']);

CollectIFAdminApp.controller('AdminHomeCtrl', ['$scope', '$http',
    function ($scope, $http) {
      $scope.selected = [];
}]);