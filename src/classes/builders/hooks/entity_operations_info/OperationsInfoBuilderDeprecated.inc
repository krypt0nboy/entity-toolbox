<?php

/**
 * Created by PhpStorm.
 * User: ddoucoure
 * Date: 08/08/16
 * Time: 10:56
 */
trait OperationsInfoBuilderTrait {

  function viewOperation() {
    return array(
      'handler'   => 'EntityToolboxOperationsView',
      'provision' => array(
        'menu'        => array(
          'default'   => TRUE,
          'menu item' => array(
            'title' => t('View'),
          ),
        ),
        'views field' => TRUE,
      ),
    );
  }

  function editOperation() {
    return array(
      'handler'   => 'EntityToolboxOperationsEdit',
      'provision' => array(
        'menu'        => array(
          'menu item' => array(
            'title' => t('Edit'),
          ),
        ),
        'views field' => TRUE,
      ),
    );
  }

  function addOperation() {
    return array(
      'handler'   => 'EntityToolboxOperationsAdd',
      'provision' => array(
        'menu' => array(
          'menu item' => array(
            'title' => t('Add'),
          ),
        ),
      ),
    );
  }

  function deleteOperation() {
    return array(
      'handler'   => 'EntityToolboxOperationsDelete',
      'provision' => array(
        'menu'        => TRUE,
        'views field' => TRUE,
      ),
    );
  }

}

class OperationsInfoBuilderEntityToolboxDependent extends EntityToolboxDependentHookBuilder {

  use OperationsInfoBuilderTrait;

  private $crudOperations = array(
    'view'   => TRUE,
    'edit'   => TRUE,
    'add'    => TRUE,
    'delete' => TRUE
  );
  //private $hook = 'operations_info';


  //($hook, $entityType, array $rawData = array())
  public function __construct($entity_type, array $values) {
    $this->hook = 'operations_info';
    parent::__construct($this->hook, $entity_type, $values);
  }


  /**
   * Build default CRUD operation and add devel Operations
   *
   * @return array
   */
  protected function buildDefault() {
    return array(
      //$this->entityInfo['entity_type'] => array(
      $this->entityType => array(
        'view'           => $this->viewOperation(),
        'edit'           => $this->editOperation(),
        'add'            => $this->addOperation(),
        'delete'         => $this->deleteOperation(),
        'devel/devel'    => array(
          'handler'   => 'EntityOperationsOperationDevel',
          'provision' => array(
            'menu' => array(
              'default secondary' => TRUE,
            ),
          ),
        ),
        'devel/token'    => array(
          'handler'   => 'EntityOperationsOperationToken',
          'provision' => array(
            'menu' => TRUE,
          ),
        ),
        'devel/metadata' => array(
          'handler'   => 'EntityOperationsOperationMetadata',
          'provision' => array(
            'menu' => TRUE,
          ),
        ),
      )
    );
  }

  /**
   * Populate Operation by CRUD
   *
   */
  private function populate() {

    if (!isset($this->rawData) || $this->rawData === TRUE) {
      $this->rawData = $this->crudOperations;
    }
    else {
      $this->rawData += array_diff_key($this->crudOperations, $this->rawData);
    }
    /*
    if( !isset($this->entityInfo[$this->tableKey]) || $this->entityInfo[$this->tableKey] === TRUE ){
      $this->entityInfo[$this->tableKey] = $this->crudOperations;
    }
    else{
      $this->entityInfo[$this->tableKey] += array_diff_key($this->crudOperations, $this->entityInfo[$this->tableKey]);
    }
    */
  }

  /**
   * Build Operation based on client provided array
   *
   * @return array
   */
  public function build() {

    $this->populate();

    foreach ($this->rawData as $verb => $operation) {
      if ($operation === FALSE) {
        continue;
      }
      if (in_array($verb, $this->crudOperations) && $operation === TRUE) {
        $methodName   = $verb . 'Operation';
        $build[$verb] = $this->{$methodName}();
        continue;
      }

      if (!isset($operation['handler'])) {
        //TODO throw Exception
        throw new Exception(t('No handler for your custom operation "@verb"', array('@verb' => $verb), array('context' => 'Custom Operation')), 1031);
      }

      $build[$verb]['handler'] = $operation['handler'];

      if (isset($operation['views'])) {
        $build[$verb]['provision'] = $operation['views'];
      }

      if (isset($operation['menu']) && is_array($operation['menu'])) {
        $build[$verb]['provision']['menu'] = array(
          'menu item'         => array('title' => $operation['menu']['title']),
          'default'           => $operation['menu']['default'],
          'default secondary' => $operation['menu']['secondary'],
          'parent tab title'  => $operation['menu']['parent'],
          'parent weight'     => $operation['menu']['parent weight'],
        );
        continue;
      }

      $build[$verb]['provision']['menu'] = ((!isset($operation['menu'])) || ($operation['menu'] === TRUE)) ? TRUE : FALSE;
    }

    $this->processedData = array($this->entityType => $build);

    /*
    foreach($this->entityInfo[$this->tableKey] as $verb => $operation) {
      if ($operation === FALSE) {
        continue;
      }
      if (in_array($verb , $this->crudOperations) && $operation === TRUE) {
        $methodName = $verb . 'Operation';
        $build[ $verb ] = $this->{$methodName}();
        continue;
      }
      
      if (!isset($operation[ 'handler'])) {
        //TODO throw Exception
        throw new MissingHandlerException(t('No handler for your custom operation "@verb"', array('@verb' => $verb), array('context' => 'Custom Operation')), 1031);
      }
      
      $build[ $verb ][ 'handler' ] = $operation[ 'handler' ];
      
      if (isset($operation[ 'views' ])) {
        $build[ $verb ][ 'provision' ][ 'menu' ] = $operation[ 'views' ];
      }
      
      if (isset($operation[ 'menu' ])) {
        
        if ($operation[ 'menu' ] === TRUE) {
          $build[ $verb ][ 'provision' ][ 'menu' ] = $operation[ 'menu' ];
        }
        if (is_array($operation[ 'menu' ])) {
          $build[ $verb ][ 'provision' ][ 'menu' ] = array (
            'menu item' => array ('title' => $operation[ 'menu' ][ 'title' ]) ,
            'default' => $operation[ 'menu' ][ 'default' ] ,
            'default secondary' => $operation[ 'menu' ][ 'secondary' ] ,
            'parent tab title' => $operation[ 'menu' ][ 'parent' ] ,
            'parent weight' => $operation[ 'menu' ][ 'parent weight' ] ,
          );
        }
      }
    }
    
    //return array($this->entityType => $build);
    */

  }

}