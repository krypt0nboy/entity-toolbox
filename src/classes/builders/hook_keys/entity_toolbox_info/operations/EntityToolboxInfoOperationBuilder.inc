<?php

/**
 * Class EntityToolboxInfoOperationBuilder
 */
class EntityToolboxInfoOperationBuilder extends EntityToolboxInfoKeyBuilder {
  /**
   * @var string $operationName
   */
  protected $operationName;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'model_class' => 'EntityToolboxInfoOperationModel'
    ), $args);
    parent::__construct($args);
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
   * @return mixed
   */
  protected function buildHandler() {
    /** @var EntityToolboxInfoOperationsBuilder $parentBuilder */
    $parentBuilder = $this->getParentBuilder();
    $return        = $parentBuilder
                       ->getRequiredOperations($this->operationName)['handler'];

    return $return;
  }

  /**
   * @return mixed
   */
  protected function buildProvision() {
    /** @var EntityToolboxInfoOperationsBuilder $parentBuilder */
    $parentBuilder = $this->getParentBuilder();
    $return        = $parentBuilder
                       ->getRequiredOperations($this->operationName)['provision'];

    return $return;
  }
}