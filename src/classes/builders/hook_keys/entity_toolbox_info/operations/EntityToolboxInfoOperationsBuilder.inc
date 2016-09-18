<?php

/**
 * Class OperationsValueBuilder
 */
class EntityToolboxInfoOperationsBuilder extends EntityToolboxInfoKeyBuilder {
  /**
   * @var array $rawOperations
   */
  protected $rawOperations = array();
  /**
   * @var array $requiredOperations
   */
  protected $requiredOperations = array();
  /**
   * @var array $missingRequiredOperations
   */
  protected $missingRequiredOperations = array();

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'self_key'            => 'operations',
      'required_operations' => array(
        'add'    => array(
          'handler'   => 'EntityToolboxOperationsAdd',
          'provision' => array(
            'menu' => TRUE
          )
        ),
        'edit'   => array(
          'handler'   => 'EntityToolboxOperationsEdit',
          'provision' => array(
            'menu'        => array(
              'default' => TRUE,
            ),
            'views field' => TRUE,
          ),
        ),
        'view'   => array(
          'handler'   => 'EntityToolboxOperationsEdit',
          'provision' => array(
            'menu'        => array(
              'default' => TRUE,
            ),
            'views field' => TRUE,
          ),
        ),
        'delete' => array(
          'handler'   => 'EntityToolboxOperationsDelete',
          'provision' => array(
            'menu'        => array(
              'default' => TRUE,
            ),
            'views field' => TRUE,
          ),
        ),
        'clone'  => array(
          'handler'   => 'EntityToolboxOperationsClone',
          'provision' => array(
            'menu' => array(
              'default' => TRUE,
            ),
          ),
        ),
      )
    ), $args);
    parent::__construct($args);
    $this->prepareStructure();
  }

  /**
   * @param string $operationName
   *
   * @return array
   */
  public function getRequiredOperations($operationName) {
    return isset($operationName) ? $this->requiredOperations[$operationName] : $this->requiredOperations;
  }

  /**
   * @param array $requiredOperations
   */
  public function setRequiredOperations($requiredOperations) {
    $this->requiredOperations = $requiredOperations;
  }

  /**
   * @return array
   */
  public function getMissingRequiredOperations() {
    return $this->missingRequiredOperations;
  }

  /**
   * @param array $missingRequiredOperations
   */
  public function setMissingRequiredOperations($missingRequiredOperations) {
    $this->missingRequiredOperations = $missingRequiredOperations;
  }

  /** {{@inheritdoc}} */
  public function build() {
    foreach ($this->getStructure() as $operationName => $operationArgs) {
      $this->setKeyBuild($operationName, $this->buildOperation($operationName));
    }
    $this->validateBuild();

    return $this->deliver();
  }

  protected function genDynamicStructure() {
    $structure          = array();
    $keyBuildersClasses = array();
    $keyBuildersArgs    = array();
    $this->extractMissingOperations();
    /** @var EntityToolboxInfoBuilder $hookBuilder */
    $hookBuilder   = $this->getHookBuilder();
    $rawOperations = $hookBuilder
      ->getRawData('operations');
    foreach ($rawOperations as $operationName => $operationInfo) {
      $structure[$operationName]          = array(
        'type'   => 'array',
        'method' => 'buildOperation'
      );
      $keyBuildersClasses[$operationName] = 'EntityToolboxInfoOperationBuilder';
      $keyBuildersArgs[$operationName]    = array(
        'operation_name' => $operationName
      );
    }
    foreach ($this->getMissingRequiredOperations() as $operationName) {
      $structure[$operationName]          = array(
        'type'   => 'array',
        'method' => 'buildOperation'
      );
      $keyBuildersClasses[$operationName] = 'EntityToolboxInfoOperationBuilder';
      $keyBuildersArgs[$operationName]    = array(
        'operation_name' => $operationName
      );
    }

    $this->setKeyBuildersClasses($keyBuildersClasses);
    $this->setKeyBuildersArgs($keyBuildersArgs);

    return $structure;
  }

  /**
   * Extract the missing required properties.
   */
  public function extractMissingOperations() {
    $types   = !empty($this->getHookBuilder()
                           ->getRawData('operations')) ? array_keys($this->getHookBuilder()
                                                                         ->getRawData('operations')) : array();
    $missing = array_diff(array_keys($this->requiredOperations), $types);
    $this->__set('missing_required_operations', $missing);
  }

  /**
   * @param $operationName
   * @return mixed
   */
  protected function buildOperation($operationName) {
    return $this->getKeyBuilder($operationName)->build();
  }
}