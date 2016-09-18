<?php

/**
 * Class EntityOperationInfoKeyOperationBuilder
 */
class EntityOperationInfoKeyOperationBuilder extends EntityOperationInfoKeyBuilder {
  /**
   * @var string $operationType
   */
  protected $operationType;
  /**
   * @var string $operationName
   */
  protected $operationName;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'model_class'          => 'EntityOperationInfoOperationModel',
        'key_builders_classes' => array(
          'provision' => 'EntityOperationInfoOperationProvisionsBuilder'
        )
      ),
      $args
    );
    parent::__construct($args);
  }

  /**
   * @return string
   */
  public function getOperationType() {
    return $this->operationType;
  }

  /**
   * @param string $operationType
   */
  public function setOperationType($operationType) {
    $this->operationType = $operationType;
  }

  /**
   * @return string
   */
  public function getOperationName() {
    return $this->operationName;
  }

  /**
   * @param string $operationName
   */
  public function setOperationName($operationName) {
    $this->operationName = $operationName;
  }

  /**
   * @return array
   */
  protected function buildProvision() {
    return $this->getKeyBuilder('provision')->build();
  }
}