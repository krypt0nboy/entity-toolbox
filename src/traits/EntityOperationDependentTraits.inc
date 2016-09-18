<?php

/**
 * Class EntityOperationDependentTraits
 */
trait EntityOperationDependentTraits {
  /**
   * @var string $operationName
   */
  protected $operationName;
  /**
   * @var array $operationInfo
   */
  protected $operationInfo = array();

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
  public function getOperationInfo() {
    return $this->operationInfo;
  }

  /**
   * @param array $operationInfo
   */
  public function setOperationInfo($operationInfo) {
    $this->operationInfo = $operationInfo;
  }
}