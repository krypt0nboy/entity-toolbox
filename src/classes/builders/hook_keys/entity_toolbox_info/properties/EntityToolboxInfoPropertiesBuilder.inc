<?php

/**
 * Class PropertiesValueBuilder
 */
class EntityToolboxInfoPropertiesBuilder extends EntityToolboxInfoKeyBuilder {
  /**
   * @var array $requiredProperties
   *   The required properties for an entity type.
   */
  protected $requiredProperties = array();
  /**
   * @var array $missingRequiredProperties
   *   The missing required properties.
   */
  protected $missingRequiredProperties = array();
  /**
   * @var array $rawProperties
   *   The raw properties info.
   */
  protected $rawProperties = array();

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key' => 'properties',
      ),
      $args
    );
    parent::__construct($args);
  }

  /**
   * {{@inheritdoc}}
   * @return \EntityToolboxInfoBuilder
   */
  public function getHookBuilder() {
    return parent::getHookBuilder();
  }

  /**
   * @return array
   */
  public function getRequiredProperties() {
    return $this->requiredProperties;
  }

  /**
   * @param array $requiredProperties
   */
  protected function setRequiredProperties($requiredProperties) {
    $this->requiredProperties = $requiredProperties;
  }

  /**
   * @return array
   */
  public function getMissingRequiredProperties() {
    return $this->missingRequiredProperties;
  }

  /**
   * @param array $missingRequiredProperties
   */
  public function setMissingRequiredProperties($missingRequiredProperties) {
    $this->missingRequiredProperties = $missingRequiredProperties;
  }

  /**
   * @return array
   */
  public function getRawProperties() {
    return $this->rawProperties;
  }

  /**
   * @param array $rawProperties
   */
  public function setRawProperties($rawProperties) {
    $this->rawProperties = $rawProperties;
  }

  /**
   * Auto set rawProperties
   */
  protected function autoSetRawProperties() {
    $hookBuilder = $this->getHookBuilder();
    $this->setRawProperties(
      $hookBuilder->getRawProperties());
  }

  /**
   * @param       $type
   * @param array $args
   * @return \EntityToolboxPropertyBase
   */
  protected function propertyTypeGetInstance($type, array $args = array()) {
    $args    = $this->mergeConstructArgs(array(
      'property_type' => $type,
      'fieldable'     => $this->fieldable,
    ), $args);
    $factory = new EntityToolboxPropertyFactory($args);

    return $factory->getInstance();
  }

  /** {{@inheritdoc}} */
  protected function prepare() {
    $this->setPhase(self::PHZ__PREP);
    $this->initTemplateVars();
    $this->prepareStructure();
    $this->alterStructure();
    $this->generateComponents();
  }

  /** {{@inheritdoc}} */
  protected function genDynamicStructure() {
    $structure          = array();
    $keyBuildersArgs    = array();
    $keyBuildersClasses = array();
    $this->autoSetRawProperties();
    $this->extractMissingPropertyTypes();
    foreach ($this->getRawProperties() as $property => $info) {
      $builderArgs                                    = $this->extractPropertyBuilderArgs($info['type'], $property, $info);
      $structure[$builderArgs['property_name']]       = array(
        'type'   => 'array',
        'method' => 'buildProperty',
      );
      $keyBuildersArgs[$builderArgs['property_name']] = $builderArgs;
    }
    foreach ($this->missingRequiredProperties as $missingRequiredProperty) {
      $builderArgs                                    = $this->extractPropertyBuilderArgs($missingRequiredProperty);
      $structure[$builderArgs['property_name']]       = array(
        'type'   => 'array',
        'method' => 'buildProperty',
      );
      $keyBuildersArgs[$builderArgs['property_name']] = $builderArgs;
    }
    foreach ($keyBuildersArgs as $key => $keyBuilderArgs) {
      /** @var EntityToolboxPropertyBase $propertyInstance */
      $propertyInstance = $keyBuilderArgs['property_instance'];
      $class            = 'EntityToolboxInfoPropertyBuilder';
      if ($keyBuilderArgs['is_reference']) {
        $reference                          = $this->extractPropertyReference($key, $propertyInstance);
        $keyBuildersArgs[$key]['reference'] = $reference;
        $class                              = $this->entityType == $reference ? 'EntityToolboxInfoSelfReferencePropertyBuilder' : 'EntityToolboxInfoReferencePropertyBuilder';
      }
      $keyBuildersClasses[$key] = $class;
    }
    $this->__set('key_builders_classes', $keyBuildersClasses);
    $this->__set('key_builders_args', $keyBuildersArgs);

    return $structure;
  }

  /**
   * Extracts a property builder args.
   *
   * @param string      $propertyType
   * @param null|string $propertyName
   * @param array       $rawPropertyInfo
   *
   * @return array
   */
  protected function extractPropertyBuilderArgs($propertyType, $propertyName = NULL, $rawPropertyInfo = array()) {
    $propertyInstance          = $this->propertyTypeGetInstance($propertyType);
    $args                      = array();
    $args['property_name']     = isset($propertyName) ? $propertyName : $this->processValueTemplate($propertyInstance->getDefaultName());
    $args['self_key']          = $args['property_name'];
    $args['property_instance'] = $propertyInstance;
    $args['property_type']     = $propertyType;
    if (!empty($rawPropertyInfo)) {
      $args['raw_property_info'] = $rawPropertyInfo;
      $args['is_reference']      = $propertyInstance->isPropertyReference();
      $args['is_multiple']       = !empty($rawPropertyInfo['multiple']) ? $rawPropertyInfo['multiple'] : $propertyInstance->getDefaultMultiple();
    }
    else {
      $args['is_reference'] = $propertyInstance->isPropertyReference();
      $args['is_multiple']  = $propertyInstance->getDefaultMultiple();
    }

    return $args;
  }

  /**
   * @param                           $propertyName
   * @param EntityToolboxPropertyBase $propertyInstance
   *
   * @return null|string
   */
  protected function extractPropertyReference($propertyName, $propertyInstance) {
    $rawReference = !empty($this->rawProperties[$propertyName]['reference']) ? $this->rawProperties[$propertyName]['reference'] : NULL;
    if (is_null($rawReference)) {
      $reference = $propertyInstance->getDefaultReference();
      $reference = $this->processValueTemplate($reference);

      return $reference;
    }
    else {
      return $rawReference;
    }
  }

  /** {{@inheritdoc}} */
  public function build() {
    foreach ($this->getStructure() as $property => $params) {
      $this->setKeyBuild($property, $this->buildProperty($property));
    }
    $this->validateBuild();

    return $this->deliver();
  }

  /**
   * Builds a property.
   *
   * @param string $property
   *   The property name.
   *
   * @return array
   */
  protected function buildProperty($property) {
    return $this->getKeyBuilder($property)->build();
  }

  /**
   * Extract the missing required properties.
   */
  public function extractMissingPropertyTypes() {
    $types = array();
    foreach ($this->getRawProperties() as $name => $property) {
      $types[] = $property['type'];
    }
    $missing = array_diff($this->requiredProperties, array_unique($types));
    $this->__set('missing_required_properties', $missing);
  }
}