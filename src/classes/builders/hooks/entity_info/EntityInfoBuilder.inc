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

  /** {{@inheritdoc}} */
  protected function setValuesBuilders() {
    parent::setValuesBuilders();
    $this->valuesBuilders['admin ui'] = new AdminUIBuilder($this->entityType);
  }

  /** {{@inheritdoc}} */
  public function build() {
    $this->processedData['label']            = $this->toolboxInfo['labels']['single'];
    $this->processedData['plural label']     = $this->toolboxInfo['labels']['plural'];
    $this->processedData['entity class']     = $this->toolboxInfo['classes']['entity'];
    $this->processedData['controller class'] = $this->toolboxInfo['classes']['controller'];
    $this->processedData['base table']       = $this->toolboxInfo['tables']['base'];
    if ($this->toolboxInfo['has_revisions']) {
      $this->processedData['revision table'] = $this->toolboxInfo['tables']['revision'];
    }
    $this->processedData['entity keys']        = $this->toolboxInfo['keys'];
    $this->processedData['label callback']     = $this->toolboxInfo['callbacks']['label'];
    $this->processedData['uri callback']       = $this->toolboxInfo['callbacks']['uri'];
    $this->processedData['creation callback']  = $this->toolboxInfo['callbacks']['creation'];
    $this->processedData['access callback']    = $this->toolboxInfo['callbacks']['access'];
    $this->processedData['module']             = $this->toolboxInfo['module'];
    $this->processedData['admin ui']           = $this->getValueBuilder('admin ui')
                                                      ->build();
    $this->processedData['inline entity form'] = array(
      'controller' => $this->toolboxInfo['classes']['inline controller']
    );

    return $this->processedData;
  }
}