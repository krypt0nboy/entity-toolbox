<?php

/**
 * Class EntityOperationsInfoRecursiveModel
 */
class EntityOperationInfoRecursiveModel extends HookRecursiveModel {
  /**
   * @var $operationType
   */
  protected $operationType;
  /**
   * @var $operationName
   */
  protected $operationName;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'hook' => 'entity_operations_info',
      ),
      $args
    );
    parent::__construct($args);
  }

  /**
   * @return mixed
   */
  public function getOperationType() {
    return $this->operationType;
  }

  /**
   * @param mixed $operationType
   */
  public function setOperationType($operationType) {
    $this->operationType = $operationType;
  }

  /**
   * @return mixed
   */
  public function getOperationName() {
    return $this->operationName;
  }

  /**
   * @param mixed $operationName
   */
  public function setOperationName($operationName) {
    $this->operationName = $operationName;
  }
}