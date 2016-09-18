<?php

/**
 * Class RelationDrupalSchemaBuilder
 */
class RelationDrupalSchemaBuilder extends DrupalSchemaBuilder {
  use PropertyDependentTraits, ReferenceDependentTraits, ReferenceDependentBuilderTraits, PropertyDependentBuilderTraits;

  /**
   * @var string $referenceProperty
   *   The reference property for which this schema is built.
   */
  protected $referenceProperty;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'key_builders_classes' => array(
        'fields' => 'RelationDrupalSchemaFieldsBuilder',
      ),
    ), $args);
    parent::__construct($args);
  }

  /**
   * @return string
   */
  public function getReferenceProperty() {
    return $this->referenceProperty;
  }

  /**
   * @param string $referenceProperty
   */
  public function setReferenceProperty($referenceProperty) {
    $this->referenceProperty = $referenceProperty;
  }

  /** {{@inheritdoc}} */
  protected function initTemplateVars(array $vars = array()) {
    $vars += $this->extractToolboxInfoPropertyTemplateVars();
    $vars += $this->extractReferenceInfoTemplateVars();
    $vars += $this->extractGroupInfoTemplateVars();
    parent::initTemplateVars($vars);
  }

  /** {{@inheritdoc}} */
  protected function buildDescription() {
    return $this->processValueTemplate('A relation table between %toolbox_info_entity_type% and %reference_info_entity_type%.');
  }

  /** {{@inheritdoc}} */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'property_name'  => $this->propertyName,
      'reference'      => $this->reference,
      'reference_info' => $this->referenceInfo,
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }
}