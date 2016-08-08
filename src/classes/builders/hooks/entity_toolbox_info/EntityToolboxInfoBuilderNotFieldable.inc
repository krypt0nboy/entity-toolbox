<?php

/**
 * Class EntityToolboxInfoBuilderNotFieldable
 *
 * Base build class for hook_entity_toolbox_info().
 */
class EntityToolboxInfoBuilderNotFieldable extends EntityToolboxInfoBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, $rawData);
  }

  /** {{@inheritdoc}} */
  protected function setValuesBuilders() {
    parent::setValuesBuilders();
    $this->valuesBuilders['properties'] = new PropertiesValueBuilderNotFieldable($this->entityType, $this->rawData);
    $this->valuesBuilders['callbacks']  = new CallbacksValueBuilder($this->entityType, $this->rawData);
    $this->valuesBuilders['operations'] = new OperationsValueBuilderNotFieldable($this->entityType, $this->rawData);
    $this->valuesBuilders['keys']       = new KeysValueBuilderNotFieldable($this->entityType, $this->rawData);
  }

  /** {{@inheritdoc}} */
  public function build() {
    parent::build();
    $this->processedData['fieldable']        = FALSE;
    $this->processedData['has_revisions']    = !empty($this->rawData['has_revisions']) ? $this->rawData['has_revisions'] : FALSE;
    $this->processedData['has_translations'] = !empty($this->rawData['has_translations']) ? $this->rawData['has_translations'] : FALSE;
    $this->processedData['exportable']       = !empty($this->rawData['has_translations']) ? $this->rawData['has_translations'] : TRUE;
    $this->processedData['bundle_of']        = !empty($this->rawData['has_translations']) ? $this->rawData['has_translations'] : preg_replace('/_type/', '', $this->entityType);
    $this->processedData['module']           = $this->rawData['module'];
    $this->processedData['properties']       = $this->getValueBuilder('properties')
                                                    ->build();
    $this->processedData['callbacks']        = $this->getValueBuilder('callbacks')
                                                    ->build();
    $this->processedData['operations']       = $this->getValueBuilder('operations')
                                                    ->build();
    $this->processedData['keys']             = $this->getValueBuilder('keys')
                                                    ->build();
    $this->processedData['group']            = '';

    return array_merge($this->processedData, $this->rawData);
  }
}