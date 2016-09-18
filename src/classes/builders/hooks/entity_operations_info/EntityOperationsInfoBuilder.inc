<?php

/**
 * Class EntityOperationsInfoBuilder
 */
class EntityOperationsInfoBuilder extends EntityToolboxDependentHookBuilder {

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'hook' => 'entity_operations_info',
    ), $args);
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  public function prepareStructure() {
    $operations         = array();
    $structure          = array();
    $keyBuildersClasses = array();
    $keyBuilders        = array();
    $keyBuildersArgs    = array();
    foreach ($this->toolboxInfo['operations'] as $operation => $params) {
      $operations[]                   = $operation;
      $structure[$operation]          = array(
        'type'   => 'array',
        'method' => 'buildOperation',
      );
      $keyBuildersClasses[$operation] = 'EntityOperationsInfoOperationBuilder';
      $keyBuildersArgs[$operation]    = array(
        'operation_name' => $operation,
        'operation_type' => !empty($params['type']) ? $params['type'] : '',
      );
    }
    $this->__set('structure', $structure);
    foreach ($operations as $operation) {
      $keyBuilders[$operation] = $this->keyBuilderGetInstance($keyBuildersClasses[$operation], $keyBuildersArgs[$operation]);
    }
    foreach ($keyBuilders as $key => $keyBuilder) {
      $this->setKeyBuilder($key, $keyBuilder);
    }
  }
}