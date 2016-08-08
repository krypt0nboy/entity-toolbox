<?php

/**
 * Class EntityInfoBuilder
 *
 * Base build class for hook_entity_info().
 */
class EntityInfoBuilder extends ContribHookBuilder {
  /**
   * EntityInfoBuilder constructor.
   * @param null|string $entityType
   */
  public function __construct($entityType) {
    parent::__construct('entity_info', $entityType);
  }

  protected function setValuesBuilders() {
    parent::setValuesBuilders();
    $this->valuesBuilders['admin ui'] = new AdminUIBuilder($this->entityType, $this->rawData);
  }

  /** {{@inheritdoc}} */
  public function build() {
    $this->processedData['label']              = $this->toolboxInfo['labels']['single'];
    $this->processedData['plural label']       = $this->toolboxInfo['labels']['plural'];
    $this->processedData['entity class']       = $this->toolboxInfo['classes']['entity'];
    $this->processedData['controller class']   = $this->toolboxInfo['classes']['controller'];
    $this->processedData['base table']         = $this->toolboxInfo['tables']['base'];
    $this->processedData['entity keys']        = $this->toolboxInfo['keys'];
    $this->processedData['module']             = $this->toolboxInfo['module'];
    $this->processedData['inline entity form'] = array(
      'controller' => $this->toolboxInfo['classes']['inline controller']
    );
    $adminUIBuilder                            = new AdminUIBuilder($this->entityType, $this->rawData);
    $this->processedData['admin ui']           = $adminUIBuilder->build();

    return $this->processedData;
  }
}